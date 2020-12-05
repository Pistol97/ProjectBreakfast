#include "Zinx.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ZinxAnimInstance.h"

AZinx::AZinx()
	: direction_to_move_(FVector::ZeroVector)
	, arm_rotation_to_(FRotator::ZeroRotator)
	, is_invoke_past_(false)
	, is_attacking_(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Initialize Component on Zinx
	spring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	spring_arm_->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	camera_->SetupAttachment(spring_arm_);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f));
	spring_arm_->TargetArmLength = 400.f;
	spring_arm_->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
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
	// Initialize AnimBP to Zinx
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		kZinxAnimation(TEXT(
			"AnimBlueprint'/Game/develop_seunghoon/Anim/Custom_Zinx_Anim_BP.Custom_Zinx_Anim_BP_C'"
		));
	if (kZinxAnimation.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(kZinxAnimation.Class);
	}
#pragma endregion
#pragma region Set Projection Value
	spring_arm_->bUsePawnControlRotation = true;
	spring_arm_->bInheritPitch = false;
	spring_arm_->bInheritRoll = false;
	spring_arm_->bInheritYaw = true;
	spring_arm_->bDoCollisionTest = true;
	bUseControllerRotationYaw = true;
	camera_->SetRelativeLocationAndRotation(FVector(220.0f, 70.0f, 20.0f)
		, FRotator(10.0f, 0.0f, 0.0f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
#pragma endregion
	GetCharacterMovement()->JumpZVelocity = kJumpMagnitude;
}

void AZinx::BeginPlay()
{
	Super::BeginPlay();
}

void AZinx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZinx::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	zinx_anim_ = Cast<UZinxAnimInstance>(GetMesh()->GetAnimInstance());
	if (zinx_anim_ == nullptr)
	{
		return;
	}
	zinx_anim_->OnMontageEnded.AddDynamic(this, &AZinx::OnAttackMontageEnded);
}

void AZinx::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Process Project's Actions for Zinx's Action
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &AZinx::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed,
		this, &AZinx::Fire);

	// Process Project's Axis for Zinx's Transform
	// D: Move Right	(กๆ)
	// A: Move Left		(ก็)
	// W: Move Forward	(ก่)
	// S: Move Backward (ก้)
	// Drag X Axis in Mouse: Rotate Zinx with Yaw
	// Drag Y Axis in Mouse: Rotate Zinx with Pitch
	PlayerInputComponent->BindAxis(TEXT("MoveVerticalAxis"), this, &AZinx::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontalAxis"), this, &AZinx::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotatePitch"), this, &AZinx::RotatePitch);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AZinx::RotateYaw);
}

#pragma region Input Event 
void AZinx::MoveForward(float input_value)
{
	if ((Controller) && (input_value != 0.0f))
	{
		const FRotator kRotation = Controller->GetControlRotation();
		const FRotator kYawRotation(0, kRotation.Yaw, 0);

		const FVector kDirection = FRotationMatrix(kYawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(kDirection, input_value);
	}
}

void AZinx::MoveHorizontal(float input_value)
{
	if ((Controller) && (input_value != 0.0f))
	{
		const FRotator kRotation = Controller->GetControlRotation();
		const FRotator kYawRotation(0, kRotation.Yaw, 0);

		const FVector kDirection = FRotationMatrix(kYawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(kDirection, input_value);
	}
}

void AZinx::RotatePitch(float input_value)
{
	AddControllerPitchInput(input_value);
}

void AZinx::RotateYaw(float input_value)
{
	AddControllerYawInput(input_value);
}

void AZinx::Fire()
{
	if (is_attacking_)
	{
		return;
	}

	zinx_anim_->PlayAttackMontage();
	is_attacking_ = true;
}

void AZinx::OnAttackMontageEnded(UAnimMontage* montage, bool is_interrupted)
{
	is_attacking_ = false;
}
#pragma endregion