

#include "Component/AttackComponent.h"

#include "GameFramework/Character.h"
#include "DataAsset/BaseCharacterData.h"
#include "Interface/AttackInterface.h"

#include "Kismet/KismetSystemLibrary.h"


UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	this->AttackInterface = TScriptInterface<IAttackInterface> (GetOwner());
}

void UAttackComponent::SetupAttackComponent(UBaseCharacterData* CharacterData)
{
	this->BaseCharacterData = CharacterData;
}

void UAttackComponent::RequestAttack()
{
	bool bCanAttack = this->bCanCombo || this->bIsAttacking == false;

	if (bCanAttack)
		Attack();
	else
		this->bSavedAttack = true;

}

void UAttackComponent::Attack()
{
	if (this->AttackInterface && this->BaseCharacterData) 
	{
		UAnimMontage* AttackMontage = GetCorrectAttackMontage();
		if (AttackMontage)
		{
			this->AttackInterface->I_PlayAnimMontage(AttackMontage);
			this->bIsAttacking = true;
			this->AttackIndex = (this->AttackIndex + 1) % this->BaseCharacterData->AttackMontages.Num();
		}
	}
}

void UAttackComponent::AN_EndAttack()
{
	this->bIsAttacking = false;
	this->bCanCombo = false;
	this->AttackIndex = 0;
}

void UAttackComponent::SetupTraceHit()
{
	this->HitCount = 0;
	this->HittedActors.Empty();
}

void UAttackComponent::TraceHit()
{
	if (this->BaseCharacterData == nullptr) return;
	if (this->AttackInterface == nullptr) return;

	FVector TraceStart = this->AttackInterface->I_GetSocketLocation(this->BaseCharacterData->TraceStart);
	FVector TraceEnd = this->AttackInterface->I_GetSocketLocation(this->BaseCharacterData->TraceEnd);

	TArray<FHitResult> HitResults;

	bool bDoHitSomeThing = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		TraceStart,
		TraceEnd,
		this->BaseCharacterData->TraceRadius,
		this->BaseCharacterData->TraceObjectTypes,
		false,
		this->BaseCharacterData->ActorsToIgnore,
		this->BaseCharacterData->bDrawDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
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

		HandleHitResult(Result);

		this->HitCount++;
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

void UAttackComponent::AN_Combo()
{
	this->bCanCombo = true;

	if (this->bSavedAttack)
	{
		RequestAttack();
		this->bSavedAttack = false;
	}
}

void UAttackComponent::HandleHitResult(const FHitResult& Result)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Red,
			Result.BoneName.ToString()
		);

	if (this->HitSomeThingDelegate.IsBound())
		this->HitSomeThingDelegate.Execute(Result);
}

UAnimMontage* UAttackComponent::GetCorrectAttackMontage()
{
	if (this->BaseCharacterData == nullptr) return nullptr;
	if (this->BaseCharacterData->AttackMontages.IsEmpty()) return nullptr;

	return this->BaseCharacterData->AttackMontages[this->AttackIndex];
}








