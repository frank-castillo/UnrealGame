// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../../AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "NGameMode.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * This improves compile times by not exporting everything for classes that do not need all of
   their functions accessible in other modules.
 */
UCLASS()
class SURVIVALGAME_API ANGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    ANGameMode();

    virtual void StartPlay() override;

    void OnActorKilled(AActor* VictimActor, AActor* Killer);

    void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:
    
    UFUNCTION()
    void SpawnBotTimerElapsed();

    UFUNCTION()
    void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

    UFUNCTION()
    void RespawnPlayerElapsed(AController* Controller);

    UPROPERTY(EditDefaultsOnly, Category = "Respawn")
    float RespawnDelay;

    FTimerHandle TimerHandle_SpawnBots;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float SpawnTimerInterval;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float MaxBotCount;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UCurveFloat* DifficultyCurve;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UEnvQuery* SpawnBotQuery;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    TSubclassOf<AActor> MinionClass;
};
