
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FHitSomeThingDelegate, const FHitResult&, HitResult);

class UAnimMontage;
class UBaseCharacterData;
class IAttackInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_FIRSTPERSONAL_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UAttackComponent();
	void SetupAttackComponent(UBaseCharacterData* CharacterData);
	void RequestAttack();
	void AN_EndAttack();
	void SetupTraceHit();
	void TraceHit();


protected:
	virtual void BeginPlay() override;

private:
	void Attack();
	void HandleHitResult(const FHitResult& Result);

public:
	FHitSomeThingDelegate HitSomeThingDelegate;

private:
	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackInterface;

	UPROPERTY()
	UBaseCharacterData* BaseCharacterData;

	bool bIsAttacking = false;

	/* Trace Hit */
	int HitCount = 0;
	TArray< AActor* > HittedActors;
		
};
