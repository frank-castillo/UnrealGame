// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <InputActionValue.h>
// .generated always has to be the last include
#include "NPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 *
 */
UCLASS()
class SURVIVALGAME_API ANPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    ANPlayerController();

    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* EvadeAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* WeaponShootAction;

    virtual void SetupInputComponent() override;

    virtual void BeginPlay();

    // Input Handlers - Functions that control the logic for input actions
    void Move(const FInputActionValue& Value);

    void Evade(const FInputActionValue& Value);

    void Shoot(const FInputActionValue& Value);
};
