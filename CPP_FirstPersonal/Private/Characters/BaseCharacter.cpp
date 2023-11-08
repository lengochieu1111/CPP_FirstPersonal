

#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "DataAsset/BaseCharacterData.h"
#include "DataAsset/EnhancedInputData.h"

#include "Component/AttackComponent.h"

#include "Kismet/GameplayStatics.h" 
#include "Kismet/KismetMathLibrary.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

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
	{
		this->AttackComponent->HitSomeThingDelegate.BindDynamic(this, &ABaseCharacter::HandleHitSomeThing);
		this->AttackComponent->SetupAttackComponent(this->BaseCharacterData);
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakePointDamage.AddDynamic(this, &ABaseCharacter::HandleTakePointDamage);

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

void ABaseCharacter::HandleHitSomeThing(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	
	const FVector AttackDirection = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), HitActor->GetActorLocation());
	
	UGameplayStatics::ApplyPointDamage(
		HitActor,
		this->BaseCharacterData->Damage,
		AttackDirection,
		HitResult,
		GetController(),
		this,
		UDamageType::StaticClass()
	);

}

void ABaseCharacter::HandleTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Red,
			FString::Printf(TEXT("Take Point Damage"))
		);

	if (this->BaseCharacterData)
	{
		UAnimMontage* HitReactMontage = GetCorrectHitReactMontage(ShotFromDirection);
		if (HitReactMontage)
			PlayAnimMontage(HitReactMontage);
	}

}

UAnimMontage* ABaseCharacter::GetCorrectHitReactMontage(const FVector& AttackDirection) const
{
	if (this->BaseCharacterData == nullptr) return nullptr;

	double Dot = FVector::DotProduct(AttackDirection, GetActorForwardVector());

	if (FMath::Abs(Dot) > 0.5)
	{
		if (Dot > 0)
			return this->BaseCharacterData->HitReactMontage_Back;
		else
			return this->BaseCharacterData->HitReactMontage_Front;
	}
	else
	{
		FVector Cross = FVector::CrossProduct(AttackDirection, GetActorForwardVector());
		if (Cross.Z > 0)
			return this->BaseCharacterData->HitReactMontage_Right;
		else
			return this->BaseCharacterData->HitReactMontage_Left;
	}

}

void ABaseCharacter::I_PlayAnimMontage(UAnimMontage* AttackMontage)
{
	PlayAnimMontage(AttackMontage);
}

void ABaseCharacter::I_AN_EndAttack()
{
	this->AttackComponent->AN_EndAttack();
}

FVector ABaseCharacter::I_GetSocketLocation(const FName& SocketName)
{
	return (GetMesh() == nullptr) ? FVector() : GetMesh()->GetSocketLocation(SocketName);
}

void ABaseCharacter::I_ANS_BeginTraceHit()
{
	if (this->AttackComponent == nullptr) return;

	this->AttackComponent->SetupTraceHit();
}

void ABaseCharacter::I_ANS_TraceHit()
{
	if (this->AttackComponent == nullptr) return;

	this->AttackComponent->TraceHit();
}

void ABaseCharacter::I_AN_Combo()
{
	if (this->AttackComponent == nullptr) return;

	this->AttackComponent->AN_Combo();
}

