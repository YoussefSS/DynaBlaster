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

}

// Called every frame
void ADestructibleWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleWallBase::Hit(AActor* OtherActor)
{
	EnablePulseMaterial();

	GetWorldTimerManager().SetTimer(HitTimerHandle, this, &ADestructibleWallBase::DestroyHelper, TimeToDestroy);
}

void ADestructibleWallBase::DestroyHelper()
{
	UWorld* World = GetWorld();

	if (World)
	{
		ensure(GoalClass != nullptr && UpgradeClass != nullptr);

		if (bIsGoalWall && GoalClass)
		{
			World->SpawnActor<AActor>(GoalClass, GetActorLocation(), FRotator(0.f));
		}

		if (bIsUpgradeWall && UpgradeClass)
		{
			World->SpawnActor<AActor>(UpgradeClass, GetActorLocation(), FRotator(0.f));
		}
	}
	

	Destroy();
}

void ADestructibleWallBase::EnablePulseMaterial()
{
	if (HitMaterial)
	{
		Mesh->SetMaterial(0, HitMaterial);
	}
}

