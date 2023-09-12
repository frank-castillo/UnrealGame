// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NGameMode.generated.h"

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

    void OnActorKilled(AActor* VictimActor, AActor* Killer);

protected:

    UFUNCTION()
    void RespawnPlayerElapsed(AController* Controller);

    UPROPERTY(EditDefaultsOnly, Category = "Respawn")
    float RespawnDelay;
};
