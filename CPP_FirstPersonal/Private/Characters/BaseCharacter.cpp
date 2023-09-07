

#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "DataAsset/EnhancedInputData.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Sprint Arm Component */
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	this->SpringArmComponent->SetupAttachment(this->RootComponent);
	this->SpringArmComponent->bUsePawnControlRotation = true;
	this->SpringArmComponent->TargetArmLength = 400.f;
	this->SpringArmComponent->AddLocalOffset(FVector(0.0f, 0.0f, 40.0f));

	/* Caamera Component */
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	this->CameraComponent->SetupAttachment(this->SpringArmComponent);
	this->CameraComponent->bUsePawnControlRotation = false;

	//
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0, 0.0, 540.0);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AddMappingContextForCharacter();

	/* Handle Input Action Look */
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent && this->EnhancedInputData && this->EnhancedInputData->IA_Look && this->EnhancedInputData->IA_Move)
	{
		EnhancedInputComponent->BindAction(this->EnhancedInputData->IA_Look, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		EnhancedInputComponent->BindAction(this->EnhancedInputData->IA_Move, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
	}


}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseCharacter::AddMappingContextForCharacter()
{
	/* Add Mapping Context */
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)  return;
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (Subsystem && this->EnhancedInputData && this->EnhancedInputData->InputMappingContext)
		Subsystem->AddMappingContext(this->EnhancedInputData->InputMappingContext, 0);
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	if (LookValue.X != 0)
		AddControllerYawInput(LookValue.X);
	
	if (LookValue.Y != 0)
		AddControllerPitchInput(LookValue.Y);

}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	FRotator MyControllerRotation = FRotator(0.0, GetControlRotation().Yaw, 0.0);

	FVector ForwardDirection = MyControllerRotation.RotateVector(FVector::ForwardVector);

	FVector RightDirection = MyControllerRotation.RotateVector(FVector::RightVector);

	if (MoveValue.X != 0)
		AddMovementInput(RightDirection, MoveValue.X);

	if (MoveValue.Y != 0)
		AddMovementInput(ForwardDirection, MoveValue.Y);

}

