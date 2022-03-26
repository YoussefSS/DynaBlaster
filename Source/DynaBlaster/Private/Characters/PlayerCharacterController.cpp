// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacterController.h"

#include "Kismet\GameplayStatics.h"
#include "Blueprint\WidgetBlueprintLibrary.h"

#include "DynaBlaster/Public/UI/DynaHUD.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

	if (HUDWidgetAsset)
	{
		HUDWidget = Cast<UDynaHUD>(CreateWidget<UUserWidget>(this, HUDWidgetAsset));
		if (HUDWidget)
		{
			HUDWidget->AddToViewport(0);
			HUDWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (PauseMenuWidgetAsset)
	{
		PauseMenuWidget = Cast<UUserWidget>(CreateWidget<UUserWidget>(this, PauseMenuWidgetAsset));
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport(0);
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WinMenuWidgetAsset)
	{
		WinMenuWidget = Cast<UUserWidget>(CreateWidget<UUserWidget>(this, WinMenuWidgetAsset));
		if (WinMenuWidget)
		{
			WinMenuWidget->AddToViewport(0);
			WinMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void APlayerCharacterController::ShowPauseMenu()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 0);

	if (PauseMenuWidget)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;

		FInputModeUIOnly InputModeUIOnly;
		SetInputMode(InputModeUIOnly);
	}
}

void APlayerCharacterController::HidePauseMenu()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1);

	if (PauseMenuWidget)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;

		FInputModeGameOnly InputModeGameOnly;
		SetInputMode(InputModeGameOnly);
	}
}

void APlayerCharacterController::ShowWinMenu()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 0);

	if (WinMenuWidget)
	{
		WinMenuWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;

		FInputModeUIOnly InputModeUIOnly;
		SetInputMode(InputModeUIOnly);
	}
}
