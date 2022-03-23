// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	ETT_Empty					UMETA(DisplayName = "Empty"),
	ETT_IndestructibleWall		UMETA(DisplayName = "IndestructibleWall"),
	ETT_DestructibleWall		UMETA(DisplayName = "DestructibleWall"),

	EMS_MAX						UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class DYNABLASTER_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitializeVirtualMap();

	void InitializeTileAt(const int32& i, const int32& j);

	void GenerateMap();

	void SpawnFloor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrintMap();

	FORCEINLINE int32 GetMapWidth() { return MapWidth + 2; }
	FORCEINLINE int32 GetMapHeight() { return MapHeight + 2; }

public:

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> IndestrucibleWallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> DestructibleWallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> FloorClass;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 MapWidth = 9;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 MapHeight = 9;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 TileWorldSize = 25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 ZSpawnLocation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 FloorSpawnZOffset = 10;

	/** 0 means will never spawn, 1 means will always spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation | Probability", meta = (ClampMin = "0", ClampMax = "1"))
	float DestructibleWallSpawnChance = 0.5;


	TMap<FVector2D, ETileType> TilesMap;

	//TArray<FMy2DArray> TilesArray;
};
