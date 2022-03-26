// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets | InGameHUD")
	TSubclassOf< UUserWidget> HUDWidgetAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets | InGameHUD")
	class UDynaHUD* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets | PauseMenu")
	TSubclassOf< UUserWidget> PauseMenuWidgetAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets | PauseMenu")
	UUserWidget* PauseMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets | WinMenu")
	TSubclassOf< UUserWidget> WinMenuWidgetAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets | WinMenu")
	UUserWidget* WinMenuWidget;


public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPauseMenu();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HidePauseMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowWinMenu();
};
