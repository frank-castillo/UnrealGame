// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NBTTask_RangedAttack.generated.h"

/**
 *
 */
UCLASS()
class SURVIVALGAME_API UNBTTask_RangedAttack : public UBTTaskNode
{
    GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
    UNBTTask_RangedAttack();

protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    float MaxBulletSpread;
};
