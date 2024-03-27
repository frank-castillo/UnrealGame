// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPlayerAttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UNPlayerAttributesComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UNPlayerAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNPlayerAttributesComponent();

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    static UNPlayerAttributesComponent* GetAttributes(AActor* FromActor);

    UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
    static bool IsActorAlive(AActor* Actor);

public:

	// EditAnywhere - edit in BP editor and per-instance in level
	// VisibleAnywhere - "read-only" in editor and level. (Use for components)
	// EditDefaultsOnly - hide variable per-instance, edit in BP editor only
	// VisibleDefaultsOnly - 'read-only' access for variable, only in BP editor (uncommon)
	// EditInstanceOnly - allow only editing of instance (e.g. when placed in level)
	// --
	// BluePrintReadOnly - 'read-only' in the Blueprint scripting (does not affect 'details' panel)
	// BluePrintReadWrite - 'read-write' access in Blueprints
	// --
	// Category = "" - display only for detail panels and blueprint context menu

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthMax() const;

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

    UFUNCTION(NetMulticast, Reliable)
    void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnAttributeChanged OnHealthChanged;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float MaxHealth;


};
