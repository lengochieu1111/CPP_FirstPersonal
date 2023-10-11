

#include "Component/AttackComponent.h"

#include "GameFramework/Character.h"
#include "DataAsset/BaseCharacterData.h"
#include "Interface/AttackInterface.h"

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

void UAttackComponent::AN_EndAttack()
{
	this->bIsAttacking = false;
}

void UAttackComponent::Attack()
{
	if (this->AttackInterface && this->BaseCharacterData)
		this->AttackInterface->I_PlayAnimMontage(this->BaseCharacterData->AttackMontage);

	this->bIsAttacking = true;
}






