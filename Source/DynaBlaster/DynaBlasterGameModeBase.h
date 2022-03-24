// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DynaBlasterGameModeBase.generated.h"

class AMapGenerator;
/**
 * 
 */
UCLASS()
class DYNABLASTER_API ADynaBlasterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AMapGenerator* GetMapGenerator();

	FVector GetLocationOnTileMap(FVector InLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DynaBlaster")
	void RestartLevel();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DynaBlaster")
	class ATopDownCamera* GetTopDownCamera();

public:

	ATopDownCamera* Cam;

	AMapGenerator* MapGenerator;
};
