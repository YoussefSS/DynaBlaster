// Copyright Epic Games, Inc. All Rights Reserved.


#include "DynaBlasterGameModeBase.h"

#include "EngineUtils.h"
#include "Kismet\GameplayStatics.h"

#include "MapGenerator.h"
#include "TopDownCamera.h"
#include "DynaBlaster\Public\Walls\DestructibleWallBase.h"
#include "DynaBlaster\Public\Saving\ScoreSaveGame.h"

void ADynaBlasterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetMapGenerator();

	LoadGame();
}

void ADynaBlasterGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SaveGame();
}

AMapGenerator* ADynaBlasterGameModeBase::GetMapGenerator()
{
	if (MapGenerator)
		return MapGenerator;

	UWorld* World = GetWorld();
	if (!World) return nullptr;

	for (TActorIterator<AMapGenerator> MapGeneratorItr(World); MapGeneratorItr; ++MapGeneratorItr)
	{
		MapGenerator = *MapGeneratorItr;
	}

	return MapGenerator;
}

FVector ADynaBlasterGameModeBase::GetLocationOnTileMap(FVector InLocation)
{
	if (!GetMapGenerator()) return InLocation;

	float TileWorldSize = GetMapGenerator()->GetTileWorldSize();

	InLocation.X = FMath::RoundToFloat(InLocation.X / TileWorldSize) * TileWorldSize;
	InLocation.Y = FMath::RoundToFloat(InLocation.Y / TileWorldSize) * TileWorldSize;

	return InLocation;
}

ATopDownCamera* ADynaBlasterGameModeBase::GetTopDownCamera()
{
	if (Cam) return Cam;

	UWorld* World = GetWorld();
	if (!World) return Cam;

	for (TActorIterator<ATopDownCamera> CameraItr(World); CameraItr; ++CameraItr)
	{
		Cam = *CameraItr;
	}

	return Cam;
}

void ADynaBlasterGameModeBase::AddUpgradeWall(ADestructibleWallBase* WallToAdd)
{
	UpgradeWalls.Add(WallToAdd);
}

TArray<ADestructibleWallBase*> ADynaBlasterGameModeBase::GetUpgradeWalls()
{
	return UpgradeWalls;
}

void ADynaBlasterGameModeBase::ShowUpgradeWalls()
{
	for (ADestructibleWallBase* Wall : UpgradeWalls)
	{
		Wall->EnablePulseMaterial();
	}
}

void ADynaBlasterGameModeBase::AddEnemy()
{
	AliveEnemyCount++;
}

void ADynaBlasterGameModeBase::RemoveEnemy(bool bAdjustScore /*= true*/)
{
	AliveEnemyCount--;

	if (AliveEnemyCount <= 0)
	{
		ShowUpgradeWalls();
	}

	if (bAdjustScore)
	{
		CurrentScore += 100;
		OnCurrentScoreChanged.Broadcast(CurrentScore);
	}
}

void ADynaBlasterGameModeBase::SaveGame()
{
	UScoreSaveGame* SaveGameInstance = Cast<UScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UScoreSaveGame::StaticClass()));

	int32 NewMax = FMath::Max(CurrentScore, Highscore);
	SaveGameInstance->Highscore = NewMax;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "DynaSave", 0);
}

void ADynaBlasterGameModeBase::LoadGame()
{
	UScoreSaveGame* LoadGameInstance = Cast<UScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UScoreSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist("DynaSave", 0)) // Check if the save game exists before loading
	{
		LoadGameInstance = Cast<UScoreSaveGame>(UGameplayStatics::LoadGameFromSlot("DynaSave", 0));

		Highscore = LoadGameInstance->Highscore;
	}
	else
	{
		Highscore = 0;
	}
}

int32 ADynaBlasterGameModeBase::GetHighScore()
{
	return Highscore;
}

