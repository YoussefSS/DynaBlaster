// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinMenu.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API UWinMenu : public UUserWidget
{
	GENERATED_BODY()
	

public:
	bool Initialize() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "WinMenu")
	class UButton* RestartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "WinMenu")
	UButton* MainMenuButton;

protected:
	UFUNCTION()
	void RestartButtonClicked();

	UFUNCTION()
	void MainMenuButtonClicked();
};
