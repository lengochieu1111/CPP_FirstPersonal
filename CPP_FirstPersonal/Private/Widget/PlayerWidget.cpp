

#include "Widget/PlayerWidget.h"
#include "Components/ProgressBar.h"

void UPlayerWidget::Update_HealthBar_Player(float NewPercent)
{
	this->HealthBar_Player->SetPercent(NewPercent);
}
