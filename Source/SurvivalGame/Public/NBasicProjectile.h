// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NProjectileBase.h"
#include "NBasicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ANBasicProjectile : public ANProjectileBase
{
	GENERATED_BODY()

public:
    ANBasicProjectile();

protected:

    UFUNCTION()
    void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void PostInitializeComponents() override;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float DamageAmount;
	
};
