// Fill out your copyright notice in the Description page of Project Settings.

#include "NPlayerAttributesComponent.h"
#include "NGameMode.h"
#include <Net/UnrealNetwork.h>

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("NI.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UNPlayerAttributesComponent::UNPlayerAttributesComponent()
{
	MaxHealth = 100.0f;
	Health = MaxHealth;

    SetIsReplicatedByDefault(true);
}

UNPlayerAttributesComponent* UNPlayerAttributesComponent::GetAttributes(AActor* FromActor)
{
    if (FromActor)
    {
        return Cast<UNPlayerAttributesComponent>(FromActor->GetComponentByClass(UNPlayerAttributesComponent::StaticClass()));
    }

    return nullptr;
}

bool UNPlayerAttributesComponent::IsActorAlive(AActor* Actor)
{
    UNPlayerAttributesComponent* AttributeComp = GetAttributes(Actor);

    if (AttributeComp)
    {
        return AttributeComp->IsAlive();
    }

    return false;
}

bool UNPlayerAttributesComponent::Kill(AActor* InstigatorActor)
{
    return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

bool UNPlayerAttributesComponent::IsAlive() const
{
    return Health > 0.0f;
}

bool UNPlayerAttributesComponent::IsFullHealth() const
{
    return Health == MaxHealth;
}

float UNPlayerAttributesComponent::GetHealthMax() const
{
    return MaxHealth;
}

float UNPlayerAttributesComponent::GetHealth() const
{
    return Health;
}

bool UNPlayerAttributesComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
    if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
    {
        return false;
    }

    if (Delta < 0.0f)
    {
        float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

        Delta *= DamageMultiplier;
    }

    float OldHealth = Health;
    float NewHealth = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);
    float ActualDelta = NewHealth - OldHealth;

    // Is Server?
    if (GetOwner()->HasAuthority())
    {
        // We only change the health if we have authority
        Health = NewHealth;

        // This method ensures we call it on the server as well as on the clients
        // When ran on clients, it will call the method upon itself, and that is it. No other server calls.
        if (ActualDelta != 0.0f)
        {
            MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
        }

        // Died
        if (ActualDelta < 0.0f && Health == 0.0f)
        {
            // Auth stands for Authority -> This is used for Multiplayer games, where the only one that can access the game mode is the authority (server)
            ANGameMode* GM = GetWorld()->GetAuthGameMode<ANGameMode>();

            if (GM)
            {
                GM->OnActorKilled(GetOwner(), InstigatorActor);
            }
        }
    }

    return ActualDelta != 0;
}

void UNPlayerAttributesComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
    OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void UNPlayerAttributesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UNPlayerAttributesComponent, Health);
    DOREPLIFETIME(UNPlayerAttributesComponent, MaxHealth);
}