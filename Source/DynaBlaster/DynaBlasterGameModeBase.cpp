// Copyright Epic Games, Inc. All Rights Reserved.


#include "DynaBlasterGameModeBase.h"

#include "EngineUtils.h"

#include "MapGenerator.h"
#include "TopDownCamera.h"
#include "DynaBlaster\Public\Walls\DestructibleWallBase.h"

void ADynaBlasterGameModeBase::BeginPlay()
{
	GetMapGenerator();

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

void ADynaBlasterGameModeBase::RemoveEnemy()
{
	AliveEnemyCount--;

	if (AliveEnemyCount <= 0)
	{
		ShowUpgradeWalls();
	}
}

