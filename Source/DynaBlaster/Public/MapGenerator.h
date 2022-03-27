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
	ETT_Enemy					UMETA(DisplayName = "Enemy"),
	ETT_Upgrade					UMETA(DisplayName = "Upgrade"),
	ETT_Goal					UMETA(DisplayName = "Goal"),

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

	void InitializeCameraPosition();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrintMap();

	FORCEINLINE int32 GetNumRows() { return Rows + 2; }
	FORCEINLINE int32 GetNumColumns() { return Columns + 2; }

	FORCEINLINE int32 GetTileWorldSize() { return TileWorldSize; }

protected:

	void SetTileToEmptyIfDestructibleWall(int32 i, int32 j);

	void SetAdjacentTilesToEmptyIfDestructibleWall(int32 i, int32 j, bool bSetMiddleTileToo = false);
public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Map Generation")
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Map Generation")
	UInstancedStaticMeshComponent* IndestructibleWallISM;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> IndestrucibleWallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<class ADestructibleWallBase> DestructibleWallClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	TSubclassOf<AActor> FloorClass;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Generation", meta = (ClampMin = "7"))
	int32 Rows = 11;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map Generation", meta = (ClampMin = "7"))
	int32 Columns = 11;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 TileWorldSize = 25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 EnemyCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation| Settings")
	int32 ZSpawnLocation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation| Settings")
	int32 FloorSpawnZOffset = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"), Category = "Map Generation| Settings")
	float CameraZOffsetMultiplier = 0.85;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation| Settings")
	float CameraZConstantOffset = 10;

	/** 0 means will never spawn, 1 means will always spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation| Probability", meta = (ClampMin = "0", ClampMax = "1"))
	float DestructibleWallSpawnChance = 0.5;

	// NOTE: Not updated after creation. NOT RELIABLE
	TMap<FVector2D, ETileType> TilesMap;

	TMap<FVector2D, ETileType> DestructibleWallsMap;

private:

	int32 EmptyTilesCount = 0;
	int32 CurrentDestructibleWallCount = 0;
	int32 InitializationAttempts = 0;

	void ShuffleArray(TArray<FVector2D>& OutArr);

	void InitializeValuesFromGameInstance();
};
