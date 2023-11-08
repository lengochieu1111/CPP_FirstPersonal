

#include "AnimInstance/BaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	this->Character = Cast<ACharacter>(TryGetPawnOwner());
	if (this->Character)
		this->MovementComponent = this->Character->GetCharacterMovement();
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (this->MovementComponent == nullptr) return;
	this->GroundSpeed = UKismetMathLibrary::VSizeXY(this->MovementComponent->Velocity);

	this->bShouldMove = this->GroundSpeed > 0;

	this->bShouldBlendLowerUpper = this->bShouldMove;

}
