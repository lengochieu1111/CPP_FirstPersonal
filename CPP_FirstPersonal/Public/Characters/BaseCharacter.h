
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AttackInterface.h"
#include "Enum/CombatState.h"
#include "BaseCharacter.generated.h"


/* Class Declaration */
class USpringArmComponent;
class UCameraComponent;

class UAttackComponent;
class UHealthComponent;

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
	//virtual void Tick(float DeltaTime) override;

		#pragma region Attack_Interface

	virtual void I_PlayAnimMontage(UAnimMontage* AttackMontage) override;
	virtual void I_PlayStartAttackSound() override;
	virtual void I_AN_EndAttack() override;

	virtual FVector I_GetSocketLocation(const FName& SocketName) override;
	virtual void I_ANS_BeginTraceHit() override;
	virtual void I_ANS_TraceHit() override;
	virtual void I_AN_Combo() override;

		#pragma endregion

protected:
	virtual void BeginPlay() override;

private:
	void AddMappingContextForCharacter();
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void AttackPressed();

	UFUNCTION()
	void HandleHitSomeThing(const FHitResult& HitResult);

	UFUNCTION()
	void HandleTakePointDamage(AActor* DamagedActor, float Damage,
		class AController* InstigatedBy, FVector HitLocation, 
		class UPrimitiveComponent* FHitComponent, FName BoneName, 
		FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UAnimMontage* GetCorrectHitReactMontage(const FVector& AttackDirection) const; 


/* PROPERTY */
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input Data")
	UEnhancedInputData* EnhancedInputData;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character Data")
	UBaseCharacterData* BaseCharacterData;

	ECombatState CombatState = ECombatState::Ready;

protected:
	UPROPERTY(VisibleAnywhere)
	UAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

/* Setter Getter */
public:
	FORCEINLINE ECombatState GetCombatState() const { return this->CombatState; }

};
