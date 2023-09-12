// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameMode.h"
#include "NPlayerController.h"
#include "NTopDownCharacter.h"
#include <EngineUtils.h>
#include <Engine/EngineTypes.h>

ANGameMode::ANGameMode()
{
    // Use custom PlayerController class we created
    PlayerControllerClass = ANPlayerController::StaticClass();
    RespawnDelay = 2.0f;

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
}

void ANGameMode::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
    ANTopDownCharacter* Player = Cast<ANTopDownCharacter>(VictimActor);

    if (Player)
    {
        // We do not store the character because if we reuse the handle, then we will never respawn the player that died as it would get overwritten
        // Using a local variable solves this as it will get instantiated in memory and live independent per character we have
        FTimerHandle TimerHandle_RespawnDelay;

        // Pass who we respawn
        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

        GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);

        UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
    }
}

void ANGameMode::RespawnPlayerElapsed(AController* Controller)
{
    if (ensure(Controller))
    {
        // Remove control and detach from us -> this ensures a proper clean copy of the character
        Controller->UnPossess();
        RestartPlayer(Controller);
    }
}
