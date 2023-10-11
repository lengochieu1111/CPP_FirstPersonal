

#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "DataAsset/BaseCharacterData.h"
#include "DataAsset/EnhancedInputData.h"

#include "Component/AttackComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Sprint Arm Component */
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	this->SpringArmComponent->SetupAttachment(this->RootComponent);
	this->SpringArmComponent->bUsePawnControlRotation = true;
	this->SpringArmComponent->TargetArmLength = 400.f;
	this->SpringArmComponent->AddLocalOffset(FVector(0.0f, 0.0f, 40.0f));

	/* Camera Component */
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	this->CameraComponent->SetupAttachment(this->SpringArmComponent);
	this->CameraComponent->bUsePawnControlRotation = false;

	/* Attack Component */
	this->AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack Component"));

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
		EnhancedInputComponent->BindAction(this->EnhancedInputData->IA_Attack, ETriggerEvent::Started, this, &ABaseCharacter::AttackPressed);
	}


}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (this->AttackComponent && this->BaseCharacterData)
		this->AttackComponent->SetupAttackComponent(this->BaseCharacterData);
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->BaseCharacterData == nullptr) return;

	FVector TraceStart = GetMesh()->GetSocketLocation(this->BaseCharacterData->TraceStart);
	FVector TraceEnd = GetMesh()->GetSocketLocation(this->BaseCharacterData->TraceEnd);

	TArray<FHitResult> HitResults;
	int HitCount = 0;

	this->HittedActors.Empty();

	bool bDoHitSomeThing = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		TraceStart,
		TraceEnd,
		this->BaseCharacterData->TraceRadius,
		this->BaseCharacterData->TraceObjectTypes,
		false,
		this->BaseCharacterData->ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		this->BaseCharacterData->DrawTime
	);

	if (bDoHitSomeThing == false) return;

	for (const FHitResult& Result : HitResults)
	{
		if (this->HittedActors.Contains(Result.GetActor())) continue;

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				-1,
				1.0f,
				FColor::Red,
				Result.BoneName.ToString()
			);

		HitCount++;
		this->HittedActors.Emplace(Result.GetActor());
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Cyan,
			FString::Printf(TEXT("Hit Count = %d"), HitCount)
		);



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

void ABaseCharacter::AttackPressed()
{
	if (this->AttackComponent)
		this->AttackComponent->RequestAttack();
}

void ABaseCharacter::I_PlayAnimMontage(UAnimMontage* AttackMontage)
{
	PlayAnimMontage(AttackMontage);
}

void ABaseCharacter::I_AN_EndAttack()
{
	this->AttackComponent->AN_EndAttack();
}

