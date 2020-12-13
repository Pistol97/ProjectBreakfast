// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "NPC_HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API UNPC_HealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void set_bar_value_percent(float const value);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* health_value = nullptr;
	
};
