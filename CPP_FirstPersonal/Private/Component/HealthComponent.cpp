

#include "Component/HealthComponent.h"
#include "DataAsset/BaseCharacterData.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHealthComponent::SetupHealthComponent(UBaseCharacterData* BCD)
{
	if (BCD)
	{
		this->Health = BCD->Health;
		this->MaxHealth = BCD->MaxHealth;
	}
}
