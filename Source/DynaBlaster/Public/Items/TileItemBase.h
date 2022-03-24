// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileItemBase.generated.h"

UCLASS()
class DYNABLASTER_API ATileItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileItemBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	/** Handling collision with a box component instead of the mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
