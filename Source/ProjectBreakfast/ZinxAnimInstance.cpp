#include "ZinxAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UZinxAnimInstance::UZinxAnimInstance()
	: current_pawn_speed_(0.0f)
	, is_jump_(false)
{
}

void UZinxAnimInstance::NativeUpdateAnimation(float delta_seconds)
{
	Super::NativeUpdateAnimation(delta_seconds);

	auto pawn = TryGetPawnOwner();	
	if (::IsValid(pawn))
	{
		current_pawn_speed_ = pawn->GetVelocity().Size();
		is_jump_ = pawn->GetMovementComponent()->IsFalling();
	}
}