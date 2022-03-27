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
	UButton* OptionsButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* QuitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu")
	UButton* OptionsBackButton;


	/** Switching between the main widget and options menu widget */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Switching")
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Switching")
	class UWidget* MainWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|Switching")
	UWidget* OptionsWidget;


	/** Map size */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|OptionsMenu")
	class USlider* RowSlider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|OptionsMenu")
	USlider* ColumnSlider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|OptionsMenu")
	class UTextBlock* RowText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "MainMenu|OptionsMenu")
	UTextBlock* ColumnText;

protected:

	virtual void NativeOnInitialized() override;

	void InitializeOptionValues();

protected:
	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void OptionsButtonClicked();

	UFUNCTION()
	void OptionsBackButtonClicked();

	UFUNCTION()
	void RowSliderChanged(float NewVal);

	UFUNCTION()
	void ColumnSliderChanged(float NewVal);

private:

	class UDynaGameInstance* GI;

	UDynaGameInstance* GetDynaGameInstance();
};
