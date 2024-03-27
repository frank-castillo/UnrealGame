// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NBTTask_RangedAttack.h"
#include "../../AIModule/Classes/AIController.h"
#include "../../Engine/Classes/GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPlayerAttributesComponent.h"

UNBTTask_RangedAttack::UNBTTask_RangedAttack()
{
    MaxBulletSpread = 2.0f;
}

EBTNodeResult::Type UNBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* MyController = OwnerComp.GetAIOwner();

    if (ensure(MyController))
    {
        ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());

        if (MyPawn == nullptr)
        {
            return EBTNodeResult::Failed;
        }

        FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front_XForward");

        AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

        if (TargetActor == nullptr)
        {
            return EBTNodeResult::Failed;
        }

        if (UNPlayerAttributesComponent::IsActorAlive(TargetActor))
        {
            return EBTNodeResult::Failed;
        }

        FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation; // Direction Vector pointing to target actor target - origin
        FRotator MuzzleRotation = Direction.Rotation();

        MuzzleRotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
        MuzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.Instigator = MyPawn;

        AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

        return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
    }

    return EBTNodeResult::Failed;
}