// Fill out your copyright notice in the Description page of Project Settings.


#include "NBasicProjectile.h"
#include "../../Engine/Classes/Components/SphereComponent.h"
#include "NGameplayFunctionLibrary.h"

ANBasicProjectile::ANBasicProjectile()
{
    SphereComp->SetSphereRadius(20.0f);
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ANBasicProjectile::OnActorOverlap);

    DamageAmount = 20.0f;
}

void ANBasicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor && OtherActor != GetInstigator())
    {
        if (UNGameplayFunctionLibrary::ApplyDamage(GetInstigator(), OtherActor, DamageAmount))
        {
            Explode();
        }
    }
}

void ANBasicProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}
