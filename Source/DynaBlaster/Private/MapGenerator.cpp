// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

#include "DrawDebugHelpers.h"
#include "Kismet\KismetArrayLibrary.h"
#include "Kismet\GameplayStatics.h"
#include "EngineUtils.h"

#include "DynaBlaster\Public\Walls\DestructibleWallBase.h"
#include "DynaBlaster\DynaBlasterGameModeBase.h"
#include "DynaBlaster\Public\DynaGameInstance.h"
#include "DynaBlaster\Public\TopDownCamera.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	IndestructibleWallISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("IndestructibleWallISM"));
	IndestructibleWallISM->SetupAttachment(RootComp);
	IndestructibleWallISM->SetCastShadow(false);

		
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeValuesFromGameInstance();

	InitializeVirtualMap();

	GenerateMap();

	InitializeCameraPosition();

	//PrintMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::InitializeVirtualMap()
{
	InitializationAttempts++;
	if (InitializationAttempts >= 5)
		verifyf(true, TEXT("Too many map initialization attempts. Either increase map size, or reduce enemy count"));

	// Initialize map tiles to Walls or Empty
	for (int32 i = 0; i < GetNumRows(); i++)
	{
		for (int32 j = 0; j < GetNumColumns(); j++)
		{
			InitializeTileAt(i, j);
		}
	}

	// Generate AI spawn locations
	for (int32 i = 0; i < EnemyCount; i++)
	{
		// Get random num in width and height. 
		int32 RandWidth = FMath::FRandRange(2, GetNumRows() - 3);
		int32 RandHeight = FMath::FRandRange(2, GetNumColumns() - 3);

		// If random ints are in an indestructible wall, increase one of them by 1
		if (RandWidth % 2 == 0 && RandHeight % 2 == 0) FMath::FRand() < 0.5 ? RandWidth++ : RandHeight++;

		// If there is already an enemy in this random location, find another location. Else add the enemy to the tilemap
		if (*TilesMap.Find(FVector2D(RandWidth, RandHeight)) == ETileType::ETT_Enemy)
			i--; 
		else
		{
			//SetAdjacentTilesToEmptyIfDestructibleWall(RandWidth, RandHeight, true); // The real DynaBlaster doesn't have this
			SetTileToEmptyIfDestructibleWall(RandWidth, RandHeight);
			TilesMap.Add(FVector2D(RandWidth, RandHeight), ETileType::ETT_Enemy);
		}
	}

	// We need a minimum of 2 destructible walls to be able to have an upgrade and goal
	if (CurrentDestructibleWallCount < 2)
	{
		//UE_LOG(LogTemp, Warning, TEXT("reinitialize tilesmap"));
		CurrentDestructibleWallCount = 0;
		InitializeVirtualMap();
		return;
	}

	// Generate upgrade and goal locations
	TArray<FVector2D> OutArr;
	DestructibleWallsMap.GenerateKeyArray(OutArr);
	ShuffleArray(OutArr);

	// Take 2 first elements after shuffling, 
	FVector2D Goal2DLocation = OutArr[0]; // Guaranteed as we check for CurrentDestructibleWallCount < 2
	TilesMap.Add(Goal2DLocation, ETileType::ETT_Goal);
	DestructibleWallsMap.Remove(Goal2DLocation);

	FVector2D Upgrade2DLocation = OutArr[1]; // Guaranteed as we check for CurrentDestructibleWallCount < 2
	TilesMap.Add(Upgrade2DLocation, ETileType::ETT_Upgrade);
	DestructibleWallsMap.Remove(Upgrade2DLocation);
}

void AMapGenerator::InitializeTileAt(const int32& i, const int32& j)
{
	if (i == 0 || i == GetNumRows() - 1 || j == 0 || j == GetNumColumns() - 1 // outer Edges
		|| (i % 2 == 0 && j % 2 == 0)) // indestructible wall every other tile
	{
		TilesMap.Add(FVector2D(i, j), ETileType::ETT_IndestructibleWall);
	}
	else // Anything that is not an indestructible wall
	{
		float randomDestructibleChance = FMath::FRand();

		if (randomDestructibleChance > DestructibleWallSpawnChance // Empty wall
			|| (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 1 && j == 2)) // Do not spawn walls in (1,1) , (2,1) , (1,2) , so that the player has an area to move in
		{
			TilesMap.Add(FVector2D(i, j), ETileType::ETT_Empty);
		}
		else // Destructible wall
		{
			TilesMap.Add(FVector2D(i, j), ETileType::ETT_DestructibleWall);
			DestructibleWallsMap.Add(FVector2D(i, j), ETileType::ETT_DestructibleWall);
			CurrentDestructibleWallCount++;
		} 
	}
}


void AMapGenerator::GenerateMap()
{
	//if (!ensureMsgf(IndestrucibleWallClass != nullptr, TEXT("IndestructibleWallClass not set"))) return;
	if (!ensureMsgf(IndestructibleWallISM, TEXT("IndestructibleWallISM is null"))) return;
	if (!ensureMsgf(DestructibleWallClass != nullptr, TEXT("DestructibleWallClass not set"))) return;
	if (!ensureMsgf(DestructibleWallClass != nullptr, TEXT("EnemyClass not set"))) return;

	UWorld* World = GetWorld();
	if (!World) return;

	ADynaBlasterGameModeBase* GM = Cast<ADynaBlasterGameModeBase>(UGameplayStatics::GetGameMode(this));

	// Spawn each tile
	for (int32 i = 0; i < GetNumRows(); i++)
	{
		for (int32 j = 0; j < GetNumColumns(); j++)
		{
			FVector SpawnLocation = FVector(i * TileWorldSize, j * TileWorldSize, ZSpawnLocation);

			switch (*TilesMap.Find(FVector2D(i, j)))
			{
				case ETileType::ETT_IndestructibleWall:
				{
					//World->SpawnActor<AActor>(IndestrucibleWallClass, SpawnLocation, FRotator(0.f));
					//FTransform SpawnTransform = );
					IndestructibleWallISM->AddInstance(FTransform(FRotator::ZeroRotator, SpawnLocation, FVector(25, 25, 25)));
					break;
				}
				case ETileType::ETT_DestructibleWall: 
				{
					World->SpawnActor<AActor>(DestructibleWallClass, SpawnLocation, FRotator(0.f));
					break;
				}
				case ETileType::ETT_Upgrade:
				{
					ADestructibleWallBase* Wall = World->SpawnActor<ADestructibleWallBase>(DestructibleWallClass, SpawnLocation, FRotator(0.f));
					Wall->SetIsUpgradeWall(true);
					//DrawDebugSphere(World, SpawnLocation, 25, 8, FColor::White, false, 5);
					
					if (GM)
					{
						GM->AddUpgradeWall(Wall);
					}
					break;
				}
				case ETileType::ETT_Goal:
				{
					ADestructibleWallBase* Wall = World->SpawnActor<ADestructibleWallBase>(DestructibleWallClass, SpawnLocation, FRotator(0.f));
					Wall->SetIsGoalWall(true);
					//DrawDebugSphere(World, SpawnLocation, 25, 8, FColor::Blue, false, 5);
					break;
				}
				case ETileType::ETT_Enemy:
				{
					World->SpawnActor<AActor>(EnemyClass, SpawnLocation, FRotator(0.f));
					// Set the spawn location of the enemy to Empty
					TilesMap.Add(FVector2D(i, j), ETileType::ETT_Empty);

					if (GM)
					{
						GM->AddEnemy();
					}
					break;
				}
				case ETileType::ETT_Empty:
				{
					break;
				}
				default: 
				{
					ensureMsgf(false, TEXT("AMapGenerator::GenerateMap() .. enum type not handled"));
					break;
				}
			}
		}
	}

	SpawnFloor();
}

void AMapGenerator::SpawnFloor()
{
	if (!ensureMsgf(FloorClass != nullptr, TEXT("FloorClass not set"))) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector SpawnLocation = FVector(TileWorldSize * GetNumRows() / 2 - TileWorldSize / 2, TileWorldSize * GetNumColumns() / 2 - TileWorldSize / 2, ZSpawnLocation - TileWorldSize / 2 - FloorSpawnZOffset);
	AActor* Actor = World->SpawnActor<AActor>(FloorClass, SpawnLocation, FRotator(0.f));
	Actor->SetActorScale3D(FVector(TileWorldSize * GetNumRows(), TileWorldSize * GetNumColumns(), FloorSpawnZOffset));
}

void AMapGenerator::InitializeCameraPosition()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FVector MapStart = FVector(GetActorLocation());
	FVector MapEnd = FVector(GetNumRows() * TileWorldSize, GetNumColumns() * TileWorldSize, GetActorLocation().Z);
	FVector MidPoint = (MapStart + MapEnd) / 2;
	float MapDistance = FVector::Dist(MapStart, MapEnd);
	MidPoint.Z = MapDistance*CameraZOffsetMultiplier + CameraZConstantOffset;
	
	for (TActorIterator<ATopDownCamera> CameraItr(World); CameraItr; ++CameraItr)
	{
		CameraItr->SetActorLocation(MidPoint);
	}
}

void AMapGenerator::PrintMap()
{
	FString MapString = "";

	for (int32 i = 0; i < GetNumRows(); i++)
	{
		MapString = "";
		for (int32 j = 0; j < GetNumColumns(); j++)
		{
			ETileType TileType = *TilesMap.Find(FVector2D(i, j));
			MapString = MapString + UEnum::GetDisplayValueAsText(TileType).ToString();
			MapString += " ";
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MapString);
	}
}

void AMapGenerator::SetTileToEmptyIfDestructibleWall(int32 i, int32 j)
{
	if (*TilesMap.Find(FVector2D(i, j)) == ETileType::ETT_DestructibleWall)
	{
		TilesMap.Add(FVector2D(i, j), ETileType::ETT_Empty);
		DestructibleWallsMap.Remove(FVector2D(i, j));
		CurrentDestructibleWallCount--;
	}
}

void AMapGenerator::SetAdjacentTilesToEmptyIfDestructibleWall(int32 i, int32 j, bool bSetMiddleTileToo /*= false*/)
{
	SetTileToEmptyIfDestructibleWall(i - 1, j);
	SetTileToEmptyIfDestructibleWall(i + 1, j);
	SetTileToEmptyIfDestructibleWall(i, j - 1);
	SetTileToEmptyIfDestructibleWall(i, j + 1);

	if (bSetMiddleTileToo)
		SetTileToEmptyIfDestructibleWall(i, j);
}

void AMapGenerator::ShuffleArray(TArray<FVector2D>& OutArr)
{
	const int32 NumShuffles = OutArr.Num() - 1;
	for (int32 i = 0; i < NumShuffles; ++i)
	{
		int32 SwapIdx = FMath::RandRange(i, NumShuffles);
		OutArr.Swap(i, SwapIdx);
	}
}

void AMapGenerator::InitializeValuesFromGameInstance()
{
	UDynaGameInstance* GI = Cast<UDynaGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GI)
	{
		Rows = GI->GetNumRows();
		Columns = GI->GetNumColumns();
		EnemyCount = GI->GetNumEnemies();
	}
}

