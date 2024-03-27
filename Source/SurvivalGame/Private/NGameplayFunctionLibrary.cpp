// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameplayFunctionLibrary.h"
#include "NPlayerAttributesComponent.h"

bool UNGameplayFunctionLibrary::ApplyDamage(AActor* DamageInstigator, AActor* TargetActor, float DamageAmount)
{
    UNPlayerAttributesComponent* AttributeComponent = UNPlayerAttributesComponent::GetAttributes(TargetActor);

    if (AttributeComponent)
    {
        return AttributeComponent->ApplyHealthChange(DamageInstigator, -DamageAmount);
    }

    return false;
}

bool UNGameplayFunctionLibrary::ApplyHealing(AActor* HealingInstigator, AActor* TargetActor, float HealingAmount)
{
    UNPlayerAttributesComponent* AttributeComponent = UNPlayerAttributesComponent::GetAttributes(TargetActor);

    if (AttributeComponent)
    {
        return AttributeComponent->ApplyHealthChange(HealingInstigator, HealingAmount);
    }

    return false;
}
