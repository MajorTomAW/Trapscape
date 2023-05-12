// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameOverlay.h"

void UWGameOverlay::UpdateHealthbar(float HealthPercentage)
{
	Healthbar->SetPercent(HealthPercentage);
}
