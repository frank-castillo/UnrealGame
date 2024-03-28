// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameMode.h"
#include "NPlayerController.h"
#include "NTopDownCharacter.h"
#include <EngineUtils.h>
#include <Engine/EngineTypes.h>
#include "../../AIModule/Classes/EnvironmentQuery/EnvQueryManager.h"
#include "../../AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "NAICharacter.h"
#include "NPlayerAttributesComponent.h"

ANGameMode::ANGameMode()
{
    // Set Default pawn class to be our Blueprint character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/TopDownCharacter_BP"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // set default controller to our Blueprinted controller
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/PlayerController_BP"));
    if (PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }

    // Use custom PlayerController class we created
    //PlayerControllerClass = ANPlayerController::StaticClass();
    RespawnDelay = 2.0f;
    SpawnTimerInterval = 2.0f;
    MaxBotCount = 20.0f;
}

void ANGameMode::StartPlay()
{
    Super::StartPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ANGameMode::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ANGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
    ANTopDownCharacter* Player = Cast<ANTopDownCharacter>(VictimActor);

    if (Player)
    {
        AController* MyPlayerController = Player->GetController();
        MyPlayerController->UnPossess();

        // We do not store the character because if we reuse the handle, then we will never respawn the player that died as it would get overwritten
        // Using a local variable solves this as it will get instantiated in memory and live independent per character we have
        FTimerHandle TimerHandle_RespawnDelay;

        // Pass who we respawn
        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "RespawnPlayerElapsed", MyPlayerController);

        GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);

        UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
    }
}

void ANGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void ANGameMode::RespawnPlayerElapsed(AController* Controller)
{
    if (ensure(Controller))
    {
        // Remove control and detach from us -> this ensures a proper clean copy of the character
        //Controller->UnPossess();
        RestartPlayer(Controller);
    }
}

void ANGameMode::SpawnBotTimerElapsed()
{
    int32 NumberOfAliveBots = 0;
    for (TActorIterator<ANAICharacter> It(GetWorld()); It; ++It)
    {
        ANAICharacter* Bot = *It;

        UNPlayerAttributesComponent* AttributeComponent = UNPlayerAttributesComponent::GetAttributes(Bot);
        if (ensure(AttributeComponent) && AttributeComponent->IsAlive())
        {
            NumberOfAliveBots++;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Found %i alive bots!"), NumberOfAliveBots);

    if (DifficultyCurve)
    {
        MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
    }

    if (NumberOfAliveBots >= MaxBotCount)
    {
        UE_LOG(LogTemp, Warning, TEXT("At Max bot capacity! Skipping spawn."))
            return;
    }

    UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

    if (ensure(QueryInstance))
    {
        QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ANGameMode::OnQueryCompleted);
    }
}

void ANGameMode::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
    if (QueryStatus != EEnvQueryStatus::Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed"));
        return;
    }

    TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

    if (Locations.IsValidIndex(0))
    {
        GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
    }
}

