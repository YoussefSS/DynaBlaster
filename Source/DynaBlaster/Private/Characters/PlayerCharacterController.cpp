// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacterController.h"

#include "DynaBlaster/Public/UI/DynaHUD.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();


	if (HUDWidgetAsset)
	{
		HUDWidget = Cast<UDynaHUD>(CreateWidget<UUserWidget>(this, HUDWidgetAsset));
		if (HUDWidget)
		{
			HUDWidget->AddToViewport(0);
			HUDWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
