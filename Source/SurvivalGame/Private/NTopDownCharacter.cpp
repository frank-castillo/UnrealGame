// Fill out your copyright notice in the Description page of Project Settings.


#include "NTopDownCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NPlayerAttributesComponent.h"

// Sets default values
ANTopDownCharacter::ANTopDownCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 1200.0f;
    SpringArmComp->bUsePawnControlRotation = false;
    SpringArmComp->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
    SpringArmComp->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->FieldOfView = 50.0f;
    CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    AttributeComp = CreateDefaultSubobject<UNPlayerAttributesComponent>(TEXT("AttributeComp"));

    MoveSpeed = 100.0f;

    //Setting class variables of the Character movement component
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void ANTopDownCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ANTopDownCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

// Called every frame
void ANTopDownCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}