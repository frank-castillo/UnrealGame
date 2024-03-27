// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NBTService_CheckAttackRange.h"
#include "../../AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "../../AIModule/Classes/AIController.h"

UNBTService_CheckAttackRange::UNBTService_CheckAttackRange()
{
    MaxAttackRange = 1000;
}

void UNBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Check distance between AI pawn and targetActor
    // Get the Blackboard comp that belongs to the owning behaviour tree
    UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

    if (ensure(BlackBoardComp))
    {
        AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

        if (TargetActor)
        {
            // Here we are getting our custom AI controller so that we can then access the respective AIPawn running this service
            AAIController* MyController = OwnerComp.GetAIOwner();

            APawn* AIPawn = MyController->GetPawn();

            if (ensure(AIPawn)) // Make sure we have a valid AI pawn
            {
                float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

                bool bWithinRange = DistanceTo < MaxAttackRange;

                // Line of sight is already part of the AIController
                bool bHasLineOfSight = false;

                if (bWithinRange)
                {
                    bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
                }

                // With the predefined blackboard variable, we can automatically get the name or value of the key and use it with the blackboard's functions
                BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLineOfSight));
            }
        }
    }
}
