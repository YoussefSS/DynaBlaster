// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeVirtualMap();

	GenerateMap();

	//PrintMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::InitializeVirtualMap()
{
	// Generate outer walls
	for (int32 i = 0; i < GetMapWidth(); i++)
	{
		for (int32 j = 0; j < GetMapHeight(); j++)
		{
			if (i == 0 || i == GetMapWidth() - 1 || j == 0 || j == GetMapHeight() - 1 // outer Edges
				|| (i % 2 == 0 && j % 2 == 0) ) // indestructible wall every other tile
			{
				TilesMap.Add(FVector2D(i, j), ETileType::ETT_IndestructibleWall);
			}
			else
			{
				TilesMap.Add(FVector2D(i, j), ETileType::ETT_Empty);
			}
			
		}

	}

	// Generate indestructible walls
	
	// Generate destructible walls

	// ?? Generate AI positions ??

	return;
}


void AMapGenerator::GenerateMap()
{
	//AActor* test;
	if (!ensureMsgf(IndestrucibleWallClass != nullptr, TEXT("IndestructibleWallClass not set"))) return;
	if (!ensureMsgf(DestructibleWallClass != nullptr, TEXT("DestructibleWallClass not set"))) return;

	UWorld* World = GetWorld();
	if (!World) return;

	// Spawn each tile
	for (int32 i = 0; i < GetMapWidth(); i++)
	{
		for (int32 j = 0; j < GetMapHeight(); j++)
		{
			FVector SpawnLocation = FVector(i * TileWorldSize, j * TileWorldSize, ZSpawnLocation);

			switch (*TilesMap.Find(FVector2D(i, j)))
			{
				case ETileType::ETT_IndestructibleWall:
				{
					AActor* Actor = World->SpawnActor<AActor>(IndestrucibleWallClass, SpawnLocation, FRotator(0.f));
					break;
				}
				case ETileType::ETT_DestructibleWall: 
				{
					// Spawn destructible wall
					break;
				}
				default: 
				{
					// enum not handled	
					break;
				}
			}
		}
	}

	// Spawn floor
	FVector SpawnLocation = FVector(TileWorldSize * GetMapWidth() / 2 - TileWorldSize/2, TileWorldSize * GetMapHeight() / 2 - TileWorldSize/2, ZSpawnLocation - TileWorldSize/2 - FloorSpawnZOffset);
	AActor* Actor = World->SpawnActor<AActor>(FloorClass, SpawnLocation, FRotator(0.f));
	Actor->SetActorScale3D(FVector(TileWorldSize * GetMapWidth() , TileWorldSize * GetMapHeight(), FloorSpawnZOffset));
}

void AMapGenerator::PrintMap()
{
	FString MapString = "";

	for (int32 i = 0; i < GetMapWidth(); i++)
	{
		MapString = "";
		for (int32 j = 0; j < GetMapHeight(); j++)
		{
			ETileType TileType = *TilesMap.Find(FVector2D(i, j));
			MapString = MapString + UEnum::GetDisplayValueAsText(TileType).ToString();
			MapString += " ";
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MapString);

	}
}

