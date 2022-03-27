// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API UScoreSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UScoreSaveGame();

	UPROPERTY(VisibleAnywhere)
	int32 Highscore;
};
