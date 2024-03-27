// Fill out your copyright notice in the Description page of Project Settings.


#include "NProjectileBase.h"
#include "../../Engine/Classes/Components/SphereComponent.h"
#include "../../Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ANProjectileBase::ANProjectileBase()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
    SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(RootComponent);

    MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
    MoveComp->bRotationFollowsVelocity = true;
    MoveComp->bInitialVelocityInLocalSpace = true;
    MoveComp->ProjectileGravityScale = 0.0f;
    MoveComp->InitialSpeed = 5000.0f;

    bReplicates = true;
}

void ANProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Explode();
}

// We need _Implementation because it was marked BlueprintNativeEvent. This way C++ can detect the implementation
void ANProjectileBase::Explode_Implementation()
{
    if (ensure(!IsPendingKill()))
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
        Destroy();
    }
}

void ANProjectileBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SphereComp->OnComponentHit.AddDynamic(this, &ANProjectileBase::OnActorHit);
}
