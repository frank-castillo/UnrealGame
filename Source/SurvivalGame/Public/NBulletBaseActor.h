// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBulletBaseActor.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(ABSTRACT)
class SURVIVALGAME_API ANBulletBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANBulletBaseActor();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* SphereComp;

    // Virtual so we can override on child classes
    UFUNCTION()
    virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // Blueprint NativeEvent = C++ base implementation, can be expanded in Blueprints
    // BlueprintCallable to allow child classes to trigger explosions
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Collide();

    virtual void PostInitializeComponents() override;
};
