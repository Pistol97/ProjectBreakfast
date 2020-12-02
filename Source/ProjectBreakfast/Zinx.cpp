#include "Zinx.h"

AZinx::AZinx()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Initialize Component 
	spring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	spring_arm_->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	camera_->SetupAttachment(spring_arm_);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f));
	spring_arm_->TargetArmLength = 400.f;
	spring_arm_->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	// Set Skeletal Mesh for Zinx
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		kZinxCardboard(TEXT(
			"SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"
		));
	if (kZinxCardboard.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(kZinxCardboard.Object);
	}
	
	// Set Animation for Zinx
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> 
		kZinxAnimation(TEXT(
			"AnimBlueprint'/Game/ParagonZinx/Characters/Heroes/Zinx/Zinx_AnimBlueprint.Zinx_AnimBlueprint_C'"
		));
	if (kZinxAnimation.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(kZinxAnimation.Class);
	}
}

void AZinx::BeginPlay()
{
	Super::BeginPlay();
}

void AZinx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZinx::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("VerticalAxis"), this, &AZinx::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("HorizontalAxis"), this, &AZinx::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AZinx::RotatePitch);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AZinx::RotateYaw);
}

void AZinx::MoveVertical(float input_value)
{
	AddMovementInput(GetActorForwardVector(), input_value);
}

void AZinx::MoveHorizontal(float input_value)
{
	AddMovementInput(GetActorRightVector(), input_value);
}

void AZinx::RotatePitch(float input_value)
{
	AddControllerPitchInput(input_value);
}

void AZinx::RotateYaw(float input_value)
{
	AddControllerYawInput(input_value);
}