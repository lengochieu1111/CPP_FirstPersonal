

#include "Characters/PlayerCharacter.h"
#include "Widget/PlayerWidget.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);

	if (this->PlayerWidget)
		this->PlayerWidget->AddToViewport();

}
