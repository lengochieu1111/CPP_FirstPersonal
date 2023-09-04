
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

/* Class Declaration */
class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class CPP_FIRSTPERSONAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


/* FUNCTION */
public:
	ABaseCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void Look(const FInputActionValue& Value);

/* PROPERTY */
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction* IA_Look;


};
