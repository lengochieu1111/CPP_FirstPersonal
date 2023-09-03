
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

/* Class Declaration */
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CPP_FIRSTPERSONAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


/* Function */
public:
	ABaseCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


/* Property */
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;


};
