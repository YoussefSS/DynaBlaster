// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleWallBase.generated.h"

UCLASS()
class DYNABLASTER_API ADestructibleWallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleWallBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	class UStaticMeshComponent* Mesh;

	/** Handling collision with a box component instead of the mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/** Spawn something on destroyed */

	/** Spawn powerup or goal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall | Destruct")
	bool bSpawnItemOnDestroy = false;

	UPROPERTY(EditAnywhere, Category = "Wall | Destruct")
	TSubclassOf<AActor> ItemToSpawnOnDestroy;

	UFUNCTION()
	void OnWallDestroyed(AActor* DestroyedActor);

	/** End spawn something on destroyed */

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
