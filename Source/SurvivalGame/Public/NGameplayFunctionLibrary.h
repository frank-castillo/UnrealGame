// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UNGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    static bool ApplyDamage(AActor* DamageInstigator, AActor* TargetActor, float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    static bool ApplyHealing(AActor* HealingInstigator, AActor* TargetActor, float HealingAmount);
};
