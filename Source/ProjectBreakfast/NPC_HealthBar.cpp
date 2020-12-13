// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_HealthBar.h"

void UNPC_HealthBar::NativeConstruct()
{
}

void UNPC_HealthBar::set_bar_value_percent(float const value)
{
	health_value->SetPercent(value);
}