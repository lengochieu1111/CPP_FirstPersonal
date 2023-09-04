

#include "Characters/BaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Add Mapping Context */
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)  return;
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (Subsystem == nullptr || this->InputMappingContext == nullptr) return;
	Subsystem->AddMappingContext(this->InputMappingContext, 0);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Handle Input Action Look */
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
		EnhancedInputComponent->BindAction(this->IA_Look, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	if (LookValue.X != 0)
		AddControllerYawInput(LookValue.X);
	
	if (LookValue.Y != 0)
		AddControllerPitchInput(LookValue.Y);

}

