// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	ETT_Empty					UMETA(DisplayName = "Empty"),
	ETT_IndestructableWall		UMETA(DisplayName = "IndestructableWall"),
	ETT_DestructableWall		UMETA(DisplayName = "DestructableWall"),

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

	void InitializeMap();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrintMap();

	FORCEINLINE int32 GetMapWidth() { return MapWidth + 2; }
	FORCEINLINE int32 GetMapHeight() { return MapHeight + 2; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 MapWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Generation")
	int32 MapHeight;

	TMap<FVector2D, ETileType> TilesMap;

	//TArray<FMy2DArray> TilesArray;
};
