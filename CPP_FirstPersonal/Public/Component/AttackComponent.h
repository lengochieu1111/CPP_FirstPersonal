
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


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
