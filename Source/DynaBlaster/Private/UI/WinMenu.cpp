// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WinMenu.h"

#include "Components\Button.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Kismet\GameplayStatics.h"

bool UWinMenu::Initialize()
{
	Super::Initialize();

	if (!RestartButton) return false;
	if (!MainMenuButton) return false;

	RestartButton->OnClicked.AddDynamic(this, &UWinMenu::RestartButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &UWinMenu::MainMenuButtonClicked);
	return true;
}


void UWinMenu::RestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel");
}

void UWinMenu::MainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
