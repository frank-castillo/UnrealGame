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

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 1200.0f;
    SpringArmComp->bUsePawnControlRotation = false;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->FieldOfView = 50.0f;

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

void ANTopDownCharacter::MoveForward(float AxisValue)
{
    if ((Controller != NULL) && (AxisValue != 0.0f))
    {
        // find if the direction is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

void ANTopDownCharacter::MoveRight(float AxisValue)
{
    if ((Controller != NULL) && (AxisValue != 0.0f))
    {
        // find if the direction is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, AxisValue);
    }
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

// Called to bind functionality to input
void ANTopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ANTopDownCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ANTopDownCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
}