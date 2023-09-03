

#include "Characters/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


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

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

