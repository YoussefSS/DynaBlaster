// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

public:
	bool Initialize() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	class UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* QuitButton;

protected:
	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();
};
