// Fill out your copyright notice in the Description page of Project Settings.


#include "NBulletBaseActor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ANBulletBaseActor::ANBulletBaseActor()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    RootComponent = SphereComp;

    MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
    MoveComp->bRotationFollowsVelocity = true;
    MoveComp->bInitialVelocityInLocalSpace = true;
    MoveComp->ProjectileGravityScale = 0.0;
    MoveComp->InitialSpeed = 8000.0f;
}

void ANBulletBaseActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Collide();
}

void ANBulletBaseActor::Collide_Implementation()
{

}

void ANBulletBaseActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}
