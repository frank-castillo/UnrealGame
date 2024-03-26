// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"
#include "NWwiseEvent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UNWwiseEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNWwiseEvent();

protected:

	UPROPERTY(EditAnywhere)
	class UAkAudioEvent* TestEvent;

	// Called when the game starts
	virtual void BeginPlay() override;

    int32 skillEventID;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
