// Copyright Epic Games, Inc. All Rights Reserved.


#include "DynaBlasterGameModeBase.h"

#include "EngineUtils.h"

#include "MapGenerator.h"
#include "TopDownCamera.h"

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

