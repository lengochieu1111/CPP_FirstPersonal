
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AttackInterface.h"
#include "BaseCharacter.generated.h"


/* Class Declaration */
class USpringArmComponent;
class UCameraComponent;

class UAttackComponent;

class UEnhancedInputData;
struct FInputActionValue;
class UBaseCharacterData;

UCLASS()
class CPP_FIRSTPERSONAL_API ABaseCharacter : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()


/* FUNCTION */
public:
	ABaseCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	 virtual void Tick(float DeltaTime) override;

#pragma region Attack_Interface
	virtual void I_PlayAnimMontage(UAnimMontage* AttackMontage) override;
	virtual void I_AN_EndAttack() override;

#pragma endregion



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

	UPROPERTY(EditDefaultsOnly, Category = "Base Character Data")
	UBaseCharacterData* BaseCharacterData;

	/* Trace Hit */

	TArray< AActor* > HittedActors;
};
