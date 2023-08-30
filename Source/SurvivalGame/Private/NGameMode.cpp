// Fill out your copyright notice in the Description page of Project Settings.


#include "NGameMode.h"
#include "NPlayerController.h"

ANGameMode::ANGameMode()
{
    // Use custom PlayerController class we created
    PlayerControllerClass = ANPlayerController::StaticClass();

    // Set Default pawn class to be our Blueprint character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/TopDownCharacter_BP"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // set default controller to our Blueprinted controller
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/PlayerController_BP"));
    if (PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}
