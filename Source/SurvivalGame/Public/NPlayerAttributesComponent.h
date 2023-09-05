// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPlayerAttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UNPlayerAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNPlayerAttributesComponent();

protected:

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int PlayerId;

public:

};
