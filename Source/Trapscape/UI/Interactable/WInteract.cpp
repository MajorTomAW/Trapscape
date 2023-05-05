// Fill out your copyright notice in the Description page of Project Settings.


#include "WInteract.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWInteract::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWInteract::SetupInteractUI(FText TextInteract, FText TextObjectName, bool bUseProgress)
{
	InteractText->SetText(TextInteract);
	ObjectName->SetText(TextObjectName);
	RadialProgress->SetVisibility(bUseProgress ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UWInteract::UpdateProgress(float Progress)
{
	RadialProgress->GetDynamicMaterial()->SetScalarParameterValue(FName("Percentage"), Progress);
}

void UWInteract::SendIsPressed(bool bIsPressed)
{
	PlayAnimation(Interacting, 0.0f, 1, bIsPressed ? EUMGSequencePlayMode::Forward : EUMGSequencePlayMode::Reverse, 1.0f, false);
}
