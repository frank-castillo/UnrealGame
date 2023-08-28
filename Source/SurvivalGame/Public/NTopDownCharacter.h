// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NTopDownCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNPlayerAttributesComponent;


UCLASS()
class SURVIVALGAME_API ANTopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANTopDownCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNPlayerAttributesComponent* AttributeComp;

    float MoveSpeed;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
