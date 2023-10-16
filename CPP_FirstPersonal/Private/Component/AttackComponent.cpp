

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
	if (this->bIsAttacking) return;

	Attack();
}

void UAttackComponent::Attack()
{
	if (this->AttackInterface && this->BaseCharacterData)
		this->AttackInterface->I_PlayAnimMontage(this->BaseCharacterData->AttackMontage);

	this->bIsAttacking = true;
}

void UAttackComponent::AN_EndAttack()
{
	this->bIsAttacking = false;
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








