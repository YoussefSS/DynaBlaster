// Fill out your copyright notice in the Description page of Project Settings.


#include "Walls/DestructibleWallBase.h"

#include "Components\BoxComponent.h"

// Sets default values
ADestructibleWallBase::ADestructibleWallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestructibleWallBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnDestroyed.AddDynamic(this, &ADestructibleWallBase::OnWallDestroyed);
}

void ADestructibleWallBase::OnWallDestroyed(AActor* DestroyedActor)
{
	// TODO OnWallDestroyed
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("destroyed"))); }
}

// Called every frame
void ADestructibleWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleWallBase::Hit(AActor* OtherActor)
{
	if (HitMaterial)
	{
		Mesh->SetMaterial(0, HitMaterial);
	}

	GetWorldTimerManager().SetTimer(HitTimerHandle, this, &ADestructibleWallBase::DestroyHelper, TimeToDestroy);
}

void ADestructibleWallBase::DestroyHelper()
{
	Destroy();
}

