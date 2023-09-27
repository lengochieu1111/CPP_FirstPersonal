
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

/* Class Declaration */
class USpringArmComponent;
class UCameraComponent;

class UAttackComponent;

class UEnhancedInputData;
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

	void AddMappingContextForCharacter();

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void AttackPressed();

/* PROPERTY */
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UAttackComponent* AttackComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input Data")
	UEnhancedInputData* EnhancedInputData;



};
