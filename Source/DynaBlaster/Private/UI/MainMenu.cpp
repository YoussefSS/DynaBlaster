// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "Components\Button.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Kismet\GameplayStatics.h"
#include "Components\WidgetSwitcher.h"
#include "Components\Slider.h"
#include "Components\TextBlock.h"

#include "DynaBlaster\Public\DynaGameInstance.h"

bool UMainMenu::Initialize()
{
	Super::Initialize();

	if (!StartButton) return false;
	if (!OptionsButton) return false;
	if (!QuitButton) return false;
	if (!OptionsBackButton) return false;

	if (!MenuSwitcher) return false;
	if (!MainWidget) return false;
	if (!OptionsWidget) return false;

	if (!RowSlider) return false;
	if (!ColumnSlider) return false;
	if (!EnemySlider) return false;
	if (!RowText) return false;
	if (!ColumnText) return false;
	if (!EnemyText) return false;

	StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartButtonClicked);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OptionsButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);
	OptionsBackButton->OnClicked.AddDynamic(this, &UMainMenu::OptionsBackButtonClicked);

	RowSlider->OnValueChanged.AddDynamic(this, &UMainMenu::RowSliderChanged);
	ColumnSlider->OnValueChanged.AddDynamic(this, &UMainMenu::ColumnSliderChanged);
	EnemySlider->OnValueChanged.AddDynamic(this, &UMainMenu::EnemySliderChanged);
	return true;
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeOptionValues();
}

void UMainMenu::InitializeOptionValues()
{
	if (!GetDynaGameInstance()) return;
		
	if (RowSlider && RowText)
	{
		RowSlider->SetValue(GetDynaGameInstance()->GetNumRows());
		RowText->SetText(FText::FromString(FString::FromInt(GetDynaGameInstance()->GetNumRows())));
	}

	if (ColumnSlider && ColumnText)
	{
		ColumnSlider->SetValue(GetDynaGameInstance()->GetNumColumns());
		ColumnText->SetText(FText::FromString(FString::FromInt(GetDynaGameInstance()->GetNumColumns())));
	}
}

void UMainMenu::UpdateEnemySliderMax()
{
	if (EnemySlider && RowSlider && ColumnSlider)
	{
		int32 MaxNum = FMath::Max(RowSlider->GetValue(), ColumnSlider->GetValue());
		int32 TempVal = EnemySlider->GetValue();
		EnemySlider->SetMaxValue(MaxNum);

		int32 NewVal = TempVal < MaxNum ? TempVal : MaxNum;
		EnemySlider->SetValue(NewVal);
		EnemySliderChanged(NewVal);
	}
}

void UMainMenu::StartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel");
}

void UMainMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}

void UMainMenu::OptionsButtonClicked()
{
	if (OptionsWidget && MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidget(OptionsWidget);
	}
}

void UMainMenu::OptionsBackButtonClicked()
{
	if (MainWidget && MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidget(MainWidget);
	}
}

void UMainMenu::RowSliderChanged(float NewVal)
{
	if (!GetDynaGameInstance()) return;

	GetDynaGameInstance()->SetNumRows(NewVal);

	if (RowText)
	{
		RowText->SetText(FText::FromString(FString::FromInt(NewVal)));
	}

	UpdateEnemySliderMax();
}

void UMainMenu::ColumnSliderChanged(float NewVal)
{
	if (!GetDynaGameInstance()) return;

	GetDynaGameInstance()->SetNumColumns(NewVal);

	if (ColumnText)
	{
		ColumnText->SetText(FText::FromString(FString::FromInt(NewVal)));
	}

	UpdateEnemySliderMax();
}

void UMainMenu::EnemySliderChanged(float NewVal)
{
	if (!GetDynaGameInstance()) return;

	GetDynaGameInstance()->SetNumEnemies(NewVal);

	if (EnemyText)
	{
		EnemyText->SetText(FText::FromString(FString::FromInt(NewVal)));
	}

	UE_LOG(LogTemp, Warning, TEXT("enemyslider"));

}

UDynaGameInstance* UMainMenu::GetDynaGameInstance()
{
	if (GI) return GI;

	UDynaGameInstance* NewGI = Cast<UDynaGameInstance>(UGameplayStatics::GetGameInstance(this));

	GI = NewGI;
	return GI;
}
