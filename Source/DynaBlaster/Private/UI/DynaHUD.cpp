// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DynaHUD.h"

#include "Components\TextBlock.h"
#include "Kismet\GameplayStatics.h"

#include "DynaBlaster/Public/Characters/PlayerCharacter.h"
#include "DynaBlaster\DynaBlasterGameModeBase.h"

bool UDynaHUD::Initialize()
{
	Super::Initialize();

	if (!RemainingTimeText) return false;
	if (!CurrentScoreText) return false;
	if (!HighscoreText) return false;

	return true;
}

void UDynaHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetMaxGameTime(MaxGameTime);

	ADynaBlasterGameModeBase* GM = Cast<ADynaBlasterGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->OnCurrentScoreChanged.AddDynamic(this, &UDynaHUD::OnCurrentScoreChanged);
		HighscoreText->SetText(FText::FromString(FString::FromInt(GM->GetHighScore())));
	}
	
}

void UDynaHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::Tick(MyGeometry, DeltaTime);

	
	if(!bTimeLimitReached && UGameplayStatics::GetGlobalTimeDilation(this)>=0.1)
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
		NewTimeString += FString::FromInt(FMath::CeilToInt(RemainingTime / 60));
		NewTimeString += ":";
		NewTimeString += ((int32)FMath::CeilToInt(RemainingTime) % 60) < 10 ? "0" + FString::FromInt(FMath::CeilToInt(RemainingTime) % 60) : FString::FromInt(FMath::CeilToInt(RemainingTime) % 60); // If less than 10, add 0 prefix
		
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
			UGameplayStatics::PlaySound2D(this, BellRingSound);
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

void UDynaHUD::OnCurrentScoreChanged(int32 NewScore)
{
	if (CurrentScoreText)
	{
		CurrentScoreText->SetText(FText::FromString(FString::FromInt(NewScore)));
	}
}
