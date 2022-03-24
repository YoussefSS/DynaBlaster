// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DynaHUD.h"

#include "Components\TextBlock.h"
#include "Kismet\GameplayStatics.h"

#include "DynaBlaster/Public/Characters/PlayerCharacter.h"

bool UDynaHUD::Initialize()
{
	Super::Initialize();

	if (!RemainingTimeText) return false;

	return true;
}

void UDynaHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetMaxGameTime(5);
}

void UDynaHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::Tick(MyGeometry, DeltaTime);

	
	if(!bTimeLimitReached)
		UpdateRemainingTime(DeltaTime);
}

void UDynaHUD::SetMaxGameTime(float NewTime)
{
	MaxGameTime = NewTime;
	RemainingTime = NewTime;
}

void UDynaHUD::UpdateRemainingTime(float DeltaTime)
{
	if (CheckLoseCondition()) return;
	

	RemainingTime -= DeltaTime;
	if (RemainingTimeText)
	{
		FString NewTimeString = "";
		NewTimeString += FString::FromInt(FMath::Floor(RemainingTime / 60));
		NewTimeString += ":";
		NewTimeString += FString::FromInt(FMath::RoundToInt(RemainingTime) % 60);
		
		FText NewTimeText = FText::FromString(NewTimeString);
		RemainingTimeText->SetText((RemainingTime<0) ? FText::FromString("0:0") : NewTimeText);
	}

	
}

bool UDynaHUD::CheckLoseCondition()
{
	if (RemainingTime < 0)
	{
		if (BellRingSound)
		{
			UGameplayStatics::PlaySound2D(this, BellRingSound); //float VolumeMultiplier, float PitchMultiplier, float StartTime)
		}

		bTimeLimitReached = true;

		APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (PlayerChar)
		{
			PlayerChar->Hit(nullptr);
		}

		return true;
	}
	return false;
}
