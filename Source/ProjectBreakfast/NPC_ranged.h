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

	// �ѱ� ������
	//EditAnywhere �����ڸ� ���� �ѱ� ������ ���� 
	//�������Ʈ �������� ����Ʈ ��峪 ĳ������ �ƹ� �ν��Ͻ��� ���� ������ �ǿ��� ������ �� �ֽ��ϴ�. 
	//BlueprintReadWrite �����ڸ� ���ؼ��� �������Ʈ �ȿ��� �ѱ� �������� ���� ���ϰ� ������ �� �ֽ��ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	//EditDefaultsOnly �����ڴ� ������Ÿ�� Ŭ������ �������Ʈ�� �� �ν��Ͻ� �󿡼��� �ƴ϶�
	//�������Ʈ�� ����Ʈ�θ� ������ �� �ִٴ� ���Դϴ�.
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
