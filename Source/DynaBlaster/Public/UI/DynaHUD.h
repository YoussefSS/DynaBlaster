// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DynaHUD.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API UDynaHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool Initialize() override;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	class USoundBase* BellRingSound;


protected:

	virtual void NativeOnInitialized() override;

	// Called every frame
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "HUD")
	class UTextBlock* RemainingTimeText;

	/** The time the game should last in seconds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	float MaxGameTime = 240;

	float RemainingTime;

	bool bTimeLimitReached = false;

public:
	

	void SetMaxGameTime(float NewTime);

	void UpdateRemainingTime(float DeltaTime);

	/** Returns true if lose condition is true */
	bool CheckLoseCondition();
};
