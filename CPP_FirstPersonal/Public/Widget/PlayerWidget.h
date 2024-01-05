
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UProgressBar;

UCLASS()
class CPP_FIRSTPERSONAL_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Update_HealthBar_Player(float NewPercent);

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar_Player;
	
};
