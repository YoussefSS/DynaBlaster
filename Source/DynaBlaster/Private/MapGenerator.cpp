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
	
	InitializeMap();

	PrintMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::InitializeMap()
{
	// Generate outer walls
	for (int32 i = 0; i < GetMapWidth(); i++)
	{
		for (int32 j = 0; j < GetMapHeight(); j++)
		{
			if (i == 0 || i == GetMapWidth() - 1 || j == 0 || j == GetMapHeight() - 1 // outer Edges
				|| (i % 2 == 0 && j % 2 == 0) ) // indestructible wall every other tile
			{
				TilesMap.Add(FVector2D(i, j), ETileType::ETT_IndestructableWall);
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

