// Fill out your copyright notice in the Description page of Project Settings.


#include "NTopDownCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NPlayerAttributesComponent.h"
#include "NPlayerController.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/Actor.h>

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
}

// Called when the game starts or when spawned
void ANTopDownCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ANTopDownCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    AttributeComp->OnHealthChanged.AddDynamic(this, &ANTopDownCharacter::OnHealthChanged);
}

void ANTopDownCharacter::ServerSetActorRotation_Implementation(FRotator NewRotation)
{
    SetActorRotation(NewRotation);
}

void ANTopDownCharacter::LocalRotation(FRotator NewRotation)
{
    ServerSetActorRotation(NewRotation);
    SetActorRotation(NewRotation);
}

void ANTopDownCharacter::OnHealthChanged(AActor* InstigatorActor, UNPlayerAttributesComponent* OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        // Logic for getting damaged
    }

    if (NewHealth <= 0.0f && Delta < 0.0f)
    {
        APlayerController* PC = Cast<APlayerController>(this->GetController());
        DisableInput(PC);
        SetLifeSpan(5.0f);
    }
}

// Called every frame
void ANTopDownCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*if (Controller)
    {
        FHitResult MouseHit;
        Controller->GetHitResultUnderCursor(ECC_Visibility, false, MouseHit);
        FVector ImpactPoint = MouseHit.ImpactPoint;
        FRotator NewRotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ImpactPoint).Yaw, 0);
        LocalRotation(NewRotation);
    }*/
}