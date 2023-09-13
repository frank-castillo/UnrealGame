// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <InputActionValue.h>
// .generated always has to be the last include
#include "NPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);

class UInputMappingContext;
class UInputAction;
class UUserWidget;

/**
 *
 */
UCLASS()
class SURVIVALGAME_API ANPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ANPlayerController();

protected:

    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    /** Evade Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* EvadeAction;

    /** Weapon Shoot Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* WeaponShootAction;

    /** In-Game Menu Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* OpenInGameMenuAction;

    UPROPERTY(EditDefaultsOnly, Category ="UI")
    TSubclassOf<UUserWidget> PauseMenuClass;

    UPROPERTY()
    UUserWidget* PauseMenuInstance;

    UFUNCTION(BlueprintCallable)
    void TogglePauseMenu();

    UPROPERTY(BlueprintAssignable)
    FOnPawnChanged OnPawnChanged;

    // Listen for incoming player state (for clients when they join this might be a nullptr when joining a game.
    // afterwards player state will not change again as PlayerControllers maintain the same state throughout the level)
    UPROPERTY(BlueprintAssignable)
    FOnPlayerStateChanged OnPlayerStateReceived;

    void SetPawn(APawn* InPawn) override;

    // Called when player controller is ready to begin playing, good moment to initialize things like UI for which BeginPlay might be too early to set up
    // Especially in multiplayer clients where not all the data such as the PlayerState have been replicated properly for each client yet
    virtual void BeginPlayingState() override;

    // In order to keep our Blueprint implementation, we have to assign an event that can be placed in the Blueprint Editor that will be called from our CPP function
    // through the replication of the event on OnRep_PlayerState() once the server updates the client's SPlayerState
    UFUNCTION(BlueprintImplementableEvent)
    void BlueprintBeginPlayingState();

    void OnRep_PlayerState() override;

    virtual void SetupInputComponent() override;

    virtual void BeginPlay();

    // Input Handlers - Functions that control the logic for input actions
    void Move(const FInputActionValue& Value);

    void Evade(const FInputActionValue& Value);

    void Shoot(const FInputActionValue& Value);
};
