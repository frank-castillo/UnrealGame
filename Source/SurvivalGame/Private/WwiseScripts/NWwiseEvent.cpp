// Fill out your copyright notice in the Description page of Project Settings.

#include "WwiseScripts/NWwiseEvent.h"
#include "../Plugins/Wwise/Source/AkAudio/Public/Wwise/Stats/AkAudio.h"
#include "../Plugins/Wwise/Source/AkAudio/Public/AkAudioDevice.h"

// Sets default values for this component's properties
UNWwiseEvent::UNWwiseEvent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UNWwiseEvent::BeginPlay()
{
    Super::BeginPlay();

    // ...
    if (FAkAudioDevice::Get())
    {
        FAkAudioDevice::Get()->PostAkAudioEventOnActor(TestEvent, this->GetOwner());
    }
}


// Called every frame
void UNWwiseEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

