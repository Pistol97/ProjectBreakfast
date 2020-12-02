#include "Zinx.h"
#include "GameFramework/CharacterMovementComponent.h"

AZinx::AZinx()
	: current_control_mode_(EControlMode::kGta)
		, direction_to_move_(FVector::ZeroVector)
		, arm_rotation_speed_(10.0f)
		, arm_length_speed_(3.0f)
		, arm_length_to_(0.0f)
		, arm_rotation_to_(FRotator::ZeroRotator)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetControlMode(current_control_mode_);

#pragma region Initialize Component on Zinx
	spring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	spring_arm_->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	camera_->SetupAttachment(spring_arm_);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f));
	spring_arm_->TargetArmLength = 400.f;
	spring_arm_->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
#pragma endregion
#pragma region Set Mesh Skeleton For Zinx
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		kZinxCardboard(TEXT(
			"SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"
		));
	if (kZinxCardboard.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(kZinxCardboard.Object);
	}
#pragma endregion
#pragma region Set Animation for Zinx
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		kZinxAnimation(TEXT(
			"AnimBlueprint'/Game/ParagonZinx/Characters/Heroes/Zinx/Zinx_AnimBlueprint.Zinx_AnimBlueprint_C'"
		));
	if (kZinxAnimation.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(kZinxAnimation.Class);
	}
#pragma endregion
}

void AZinx::BeginPlay()
{
	Super::BeginPlay();
}

void AZinx::SetControlMode(EControlMode new_control_mode)
{
	// Check Input Value is same with Previous Control Mode
	if (current_control_mode_ == new_control_mode)
	{
		return;
	}
	else
	{
		current_control_mode_ = new_control_mode;
	}

	if (current_control_mode_ == EControlMode::kGta)
	{
		// spring_arm_->TargetArmLength = 450.f;
		// spring_arm_->SetRelativeRotation(FRotator::ZeroRotator);
		arm_length_to_ = 450.f;
		spring_arm_->bUsePawnControlRotation = true;
		spring_arm_->bInheritPitch = true;
		spring_arm_->bInheritRoll = true;
		spring_arm_->bInheritYaw = true;
		spring_arm_->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	}
	else if (current_control_mode_ == EControlMode::kDiablo)
	{
		// spring_arm_->TargetArmLength = 800.f;
		// spring_arm_->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
		arm_length_to_ = 800.f;
		arm_rotation_to_ = FRotator(-45.0f, 0.0f, 0.0f);
		spring_arm_->bUsePawnControlRotation = false;
		spring_arm_->bInheritPitch = false;
		spring_arm_->bInheritRoll = false;
		spring_arm_->bInheritYaw = false;
		spring_arm_->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	}
}

void AZinx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spring_arm_->TargetArmLength = FMath::FInterpTo
		(spring_arm_->TargetArmLength, arm_length_to_, DeltaTime,
		arm_length_speed_);

	if (current_control_mode_ == EControlMode::kDiablo)
	{
		spring_arm_->GetRelativeRotation() =
			FMath::RInterpTo(spring_arm_->GetRelativeRotation(),
			arm_rotation_to_, DeltaTime, arm_rotation_speed_);
	}

	if ((current_control_mode_ == EControlMode::kDiablo)
		&& (direction_to_move_.SizeSquared() > 0.0f))
	{
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX
		(direction_to_move_).Rotator());
		AddMovementInput(direction_to_move_);
	}
}

void AZinx::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Process Project's Actions for Zinx's Action
	// Shift + V: View Changed
	PlayerInputComponent->BindAction(TEXT("ChangeViewSpace"),
		EInputEvent::IE_Pressed, this, &AZinx::ViewChange);

	// Process Project's Axis for Zinx's Transform
	// D: Move Right	(กๆ)
	// A: Move Left		(ก็)
	// W: Move Forward	(ก่)
	// S: Move Backward (ก้)
	// Drag X Axis in Mouse: Rotate Zinx with Yaw
	// Drag Y Axis in Mouse: Rotate Zinx with Pitch
	PlayerInputComponent->BindAxis(TEXT("MoveVerticalAxis"), this, &AZinx::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontalAxis"), this, &AZinx::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotatePitch"), this, &AZinx::RotatePitch);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AZinx::RotateYaw);
}

#pragma region Input Event 
void AZinx::MoveVertical(float input_value)
{
	if (current_control_mode_ == EControlMode::kGta)
	{
		AddMovementInput(FRotationMatrix
		(GetControlRotation()).GetUnitAxis(EAxis::X), input_value);
	}
	else if (current_control_mode_ == EControlMode::kDiablo)
	{
		direction_to_move_.X = input_value;
	}
}

void AZinx::MoveHorizontal(float input_value)
{
	if (current_control_mode_ == EControlMode::kGta)
	{
		AddMovementInput(FRotationMatrix
		(GetControlRotation()).GetUnitAxis(EAxis::Y), input_value);
	}
	else if (current_control_mode_ == EControlMode::kDiablo)
	{
		direction_to_move_.Y = input_value;
	}
	
}

void AZinx::RotatePitch(float input_value)
{
	if (current_control_mode_ == EControlMode::kGta)
	{
		AddControllerPitchInput(input_value);
	}
}

void AZinx::RotateYaw(float input_value)
{
	if (current_control_mode_ == EControlMode::kGta)
	{
		AddControllerYawInput(input_value);
	}
}

void AZinx::ViewChange()
{
	if (current_control_mode_ == EControlMode::kGta)
	{
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::kDiablo);
	}
	else if (current_control_mode_ == EControlMode::kDiablo)
	{
		GetController()->SetControlRotation
			(spring_arm_->GetRelativeRotation());
		SetControlMode(EControlMode::kGta);
	}
}
#pragma endregion