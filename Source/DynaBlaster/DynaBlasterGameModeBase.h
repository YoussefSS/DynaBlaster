// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DynaBlasterGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentScoreChanged, int32, NewScore);

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
public:

	AMapGenerator* GetMapGenerator();

	FVector GetLocationOnTileMap(FVector InLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DynaBlaster")
	void RestartLevel();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DynaBlaster")
	class ATopDownCamera* GetTopDownCamera();

	void AddUpgradeWall(class ADestructibleWallBase* WallToAdd);

	TArray<ADestructibleWallBase*> GetUpgradeWalls();

	void ShowUpgradeWalls();

	void AddEnemy();

	void RemoveEnemy(bool bAdjustScore = true);

public:

	ATopDownCamera* Cam;

	AMapGenerator* MapGenerator;

private:
	TArray<ADestructibleWallBase*> UpgradeWalls;

	int32 AliveEnemyCount = 0;

private: /** Score / Saving */
	int32 CurrentScore = 0;
	int32 Highscore = 0;

public:
	FOnCurrentScoreChanged OnCurrentScoreChanged;

	void SaveGame();
	void LoadGame();

	int32 GetHighScore();
};
