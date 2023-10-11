
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;

class CPP_FIRSTPERSONAL_API IAttackInterface
{
	GENERATED_BODY()

public:
	virtual void I_PlayAnimMontage(UAnimMontage* AttackMontage) = 0;
	virtual void I_AN_EndAttack() = 0;

};
