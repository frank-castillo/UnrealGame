// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NAIController.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ANAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(BehaviourTree);
}
