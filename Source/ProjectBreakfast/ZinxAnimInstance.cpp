#include "ZinxAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UZinxAnimInstance::UZinxAnimInstance()
	: current_pawn_speed_(0.0f)
	, is_jump_(false)
{
	#pragma region Initialize Montage
	// Initialize Attack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		kAttackMontage(TEXT(
		"AnimMontage'/Game/develop_seunghoon/Anim/Zinx_Fire_Montage.Zinx_Fire_Montage'"
		));
	if (kAttackMontage.Succeeded())
	{
		attack_montage_ = kAttackMontage.Object;
	}
	#pragma endregion
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

void UZinxAnimInstance::PlayAttackMontage()
{
	Montage_Play(attack_montage_, 1.0f);	
}