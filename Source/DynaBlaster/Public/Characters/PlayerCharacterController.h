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

	/** Variable to hold the widget after creating it */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets | InGameHUD")
	class UDynaHUD* HUDWidget;

};
