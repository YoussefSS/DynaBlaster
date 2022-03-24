// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynaBlaster/Public/Items/TileItemBase.h"
#include "Bomb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBombExploded);

UCLASS()
class DYNABLASTER_API ABomb : public ATileItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

	void ExplodeOnTraceAxis(FVector AxisToTraceOn);

	void SpawnBombTraceAt(FVector SpawnLocation);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomb|Parameters")
	float TimeToExplode = 3;

	FTimerHandle BombTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bomb|Parameters")
	float TraceLengthRegular = 25;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bomb|Parameters")
	float TraceLengthUpgraded = 50;

	UPROPERTY(VisibleInstanceOnly, Category = "Bomb")
	bool bIsUpgraded = false;

	UPROPERTY(EditDefaultsOnly, Category = "Bomb|Bomb Trace")
	TSubclassOf<class ABombTrace> BombTraceClass;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnBombExploded OnBombExploded;

};
