// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBombExploded);

UCLASS()
class DYNABLASTER_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	class UStaticMeshComponent* Mesh;

	/** Handling collision with a box component instead of the mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Explode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomb | Parameters")
	float TimeToExplode = 3;

	FTimerHandle BombTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnBombExploded OnBombExploded;

};
