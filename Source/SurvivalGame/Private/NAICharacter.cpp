// Fill out your copyright notice in the Description page of Project Settings.


#include "NAICharacter.h"
#include "NPlayerAttributesComponent.h"
#include "../../AIModule/Classes/AIController.h"
#include <AIModule/Classes/BrainComponent.h>
#include "../../AIModule/Classes/Perception/PawnSensingComponent.h"
#include "../../AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "../../Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
ANAICharacter::ANAICharacter()
{
    AttributeComp = CreateDefaultSubobject<UNPlayerAttributesComponent>(TEXT("AttributeComp"));
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ANAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    AttributeComp->OnHealthChanged.AddDynamic(this, &ANAICharacter::OnHealthChanged);
    PawnSensingComp->OnSeePawn.AddDynamic(this, &ANAICharacter::OnPawnSeen);
}

void ANAICharacter::OnHealthChanged(AActor* InstigatorActor, UNPlayerAttributesComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        if (InstigatorActor != this)
        {
            SetTargetActor(InstigatorActor);
        }

        if (NewHealth <= 0.0f)
        {
            AAIController* AIC = CastChecked<AAIController>(GetController());

            if (AIC)
            {
                AIC->GetBrainComponent()->StopLogic("Killed");
            }

            // Ragdoll
            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));

            GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            GetCharacterMovement()->DisableMovement();

            SetLifeSpan(5.0f);
        }
    }
}

void ANAICharacter::OnPawnSeen(APawn* Pawn)
{
    SetTargetActor(Pawn);
}

void ANAICharacter::SetTargetActor(AActor* NewTarget)
{
    AAIController* AIC = Cast<AAIController>(GetController());

    if (AIC)
    {
        AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
    }
}
