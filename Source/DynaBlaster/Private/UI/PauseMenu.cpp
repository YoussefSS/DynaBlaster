// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"

#include "Components\Button.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Kismet\GameplayStatics.h"

#include "DynaBlaster\Public\Characters\PlayerCharacterController.h"


bool UPauseMenu::Initialize()
{
	Super::Initialize();

	if (!RestartButton) return false;
	if (!MainMenuButton) return false;
	if (!ResumeButton) return false;
	RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::RestartButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenuButtonClicked);
	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeButtonClicked);
	return true;
}

void UPauseMenu::RestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel");
}

void UPauseMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UPauseMenu::ResumeButtonClicked()
{
	APlayerCharacterController* APCC = Cast<APlayerCharacterController>(GetOwningPlayer());

	if (APCC)
	{
		APCC->HidePauseMenu();
	}
}
