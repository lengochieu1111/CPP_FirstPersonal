

#include "Component/AttackComponent.h"

#include "GameFramework/Character.h"

UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAttackComponent::RequestAttack(ACharacter* Character)
{
	if (Character)
		Character->PlayAnimMontage(this->AttackMontage);
}





