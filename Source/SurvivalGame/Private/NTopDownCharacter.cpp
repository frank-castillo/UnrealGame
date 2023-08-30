// Fill out your copyright notice in the Description page of Project Settings.


#include "NTopDownCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NPlayerAttributesComponent.h"
#include "NPlayerController.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ANTopDownCharacter::ANTopDownCharacter()
{
    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //Setting class variables of the Character movement component
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    //GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bIgnoreBaseRotation = false;
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
    SpringArmComp->TargetArmLength = 1200.0f;
    SpringArmComp->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->FieldOfView = 50.0f;
    CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    AttributeComp = CreateDefaultSubobject<UNPlayerAttributesComponent>(TEXT("AttributeComp"));

    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ANTopDownCharacter::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = CastChecked<ANPlayerController>(GetController());
}

void ANTopDownCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

// Called every frame
void ANTopDownCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerController)
    {
        FHitResult MouseHit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, MouseHit);
        FVector ImpactPoint = MouseHit.ImpactPoint;
        SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ImpactPoint).Yaw, 0));
    }
}