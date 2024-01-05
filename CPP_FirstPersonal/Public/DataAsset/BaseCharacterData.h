
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseCharacterData.generated.h"

class UAnimMontage;
class UParticleSystem;

UCLASS()
class CPP_FIRSTPERSONAL_API UBaseCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	/* 
	* Trace Hit 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	USoundBase* StartAttackSound;

	/*
	* Hit React
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Front;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Back;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Left;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactMontage_Right;

	/*
	* Trace Hit 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	TArray< TEnumAsByte< EObjectTypeQuery > > TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	TArray< AActor* > ActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	float TraceRadius = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	FName TraceStart;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	FName TraceEnd;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	float DrawTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace Hit")
	bool bDrawDebugTrace = false;

	/* 
	* Hit Impact
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Hit Impact")
	UParticleSystem* HitImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Hit Impact")
	USoundBase* HitImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Hit Impact")
	USoundBase* PainSound;

	/* Stats */
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Damage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxHealth = 100.0f;

};
