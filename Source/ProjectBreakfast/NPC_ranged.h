// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "NPC_ranged.generated.h"

UCLASS()
class PROJECTBREAKFAST_API ANPC_ranged : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_ranged();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void range_attack();

	UAnimMontage* get_montage() const;

	// 총구 오프셋
	//EditAnywhere 지정자를 통해 총구 오프셋 값을 
	//블루프린트 에디터의 디폴트 모드나 캐릭터의 아무 인스턴스에 대한 디테일 탭에서 변경할 수 있습니다. 
	//BlueprintReadWrite 지정자를 통해서는 블루프린트 안에서 총구 오프셋의 값을 구하고 설정할 수 있습니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스
	//EditDefaultsOnly 지정자는 프로젝타일 클래스를 블루프린트의 각 인스턴스 상에서가 아니라
	//블루프린트의 디폴트로만 설정할 수 있다는 뜻입니다.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ANPC_Projectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	bool bFiring = false;

};
