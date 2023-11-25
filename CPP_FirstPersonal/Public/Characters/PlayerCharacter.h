
#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerWidget;

UCLASS()
class CPP_FIRSTPERSONAL_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,  Category = "Widget")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;
	
};
