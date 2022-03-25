// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "DynaBlaster/Public/Items/TileItemBase.h"
#include "DestructibleWallBase.generated.h"

UCLASS()
class DYNABLASTER_API ADestructibleWallBase : public ATileItemBase, public IHittable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleWallBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInstance* HitMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/** Spawn something on destroyed */

	/** Spawn powerup or goal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall|Destruct")
	bool bSpawnItemOnDestroy = false;

	UPROPERTY(EditAnywhere, Category = "Wall|Destruct")
	TSubclassOf<AActor> ItemToSpawnOnDestroy;

	UFUNCTION()
	void OnWallDestroyed(AActor* DestroyedActor);

	/** End spawn something on destroyed */



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Hit(AActor* OtherActor) override;

	virtual void DestroyHelper() override;

protected:

	FTimerHandle HitTimerHandle;

	/** How long before this wall is destroyed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	float TimeToDestroy = 1.2;

};
