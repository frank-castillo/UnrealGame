// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UNBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	
public:
    UNBTService_CheckAttackRange();

protected:
    
    // Already implemented variable type that will allow to automatically select keys derived form the blackboard we are using as the main memory reference in the script
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

    /* Max desired attack range of AI pawn */
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxAttackRange;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
