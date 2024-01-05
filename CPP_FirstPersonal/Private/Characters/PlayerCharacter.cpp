

#include "Characters/PlayerCharacter.h"
#include "Widget/PlayerWidget.h"
#include "Component/HealthComponent.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);

	if (this->PlayerWidget) 
	{
		this->PlayerWidget->AddToViewport();

		this->PlayerWidget->Update_HealthBar_Player(
			this->HealthComponent->Health / this->HealthComponent->MaxHealth
		);
	}

}
