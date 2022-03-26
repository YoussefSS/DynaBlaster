// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "Components\Button.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Kismet\GameplayStatics.h"
bool UMainMenu::Initialize()
{
	Super::Initialize();

	if (!StartButton) return false;
	if (!QuitButton) return false;

	StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);
	return true;
}

void UMainMenu::StartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel");
}

void UMainMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
