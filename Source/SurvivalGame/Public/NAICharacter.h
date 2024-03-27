// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NAICharacter.generated.h"

class UNPlayerAttributesComponent;
class UPawnSensingComponent;

UCLASS()
class SURVIVALGAME_API ANAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANAICharacter();

protected:

    virtual void PostInitializeComponents() override;

    UFUNCTION()
    void OnHealthChanged(AActor* InstigatorActor, UNPlayerAttributesComponent* OwningComp, float NewHealth, float Delta);

    UFUNCTION()
    void OnPawnSeen(APawn* Pawn);

    UFUNCTION()
    void SetTargetActor(AActor* NewTarget);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNPlayerAttributesComponent* AttributeComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPawnSensingComponent* PawnSensingComp;
};
