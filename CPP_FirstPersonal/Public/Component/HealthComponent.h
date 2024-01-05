
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UBaseCharacterData;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_FIRSTPERSONAL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:	
	void SetupHealthComponent(UBaseCharacterData* BCD);

public:
	float Health = 0.0f;

	float MaxHealth = 0.0f;
		
};
