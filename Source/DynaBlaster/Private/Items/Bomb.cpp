// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bomb.h"


#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet\GameplayStatics.h"

#include "DynaBlaster/Public/Interfaces\Hittable.h"
// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(BombTimer, this, &ABomb::Explode, TimeToExplode);
}

void ABomb::Explode()
{
	// Play visual effect
	

	// Destroy adjacent tiles
	ExplodeOnTraceAxis(GetActorForwardVector());
	ExplodeOnTraceAxis(-GetActorForwardVector());
	ExplodeOnTraceAxis(GetActorRightVector());
	ExplodeOnTraceAxis(-GetActorRightVector());

	
	SpawnExplosionParticleAt(GetActorLocation());

	OnBombExploded.Broadcast();
	Destroy();
}

void ABomb::ExplodeOnTraceAxis(FVector AxisToTraceOn)
{
	// Set trace ends
	FVector TraceEndRegular = GetActorLocation() + AxisToTraceOn * TraceLengthRegular;
	FVector TraceEndUpgraded = GetActorLocation() + AxisToTraceOn * TraceLengthUpgraded;
	FVector FinalTraceEnd;
	
	if (!bIsUpgraded)
	{
		FinalTraceEnd = TraceEndRegular;
	}
	else
	{
		FinalTraceEnd = TraceEndUpgraded;
	}
		
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), FinalTraceEnd, ECC_Visibility, QueryParams)) // Single as we only need to destroy the first hittable we touch
	{
		// If upgraded, do another hit test with the regular trace end, if there is nothing there, spawn a particle
		FHitResult CloseHit;
		bool bCloseRangeHit = true;
		if (bIsUpgraded && !GetWorld()->LineTraceSingleByChannel(CloseHit, GetActorLocation(), TraceEndRegular, ECC_Visibility, QueryParams)) // If upgraded, spawn a particle at the regular position
		{
			bCloseRangeHit = false;
		}

		// Check for hittable
		IHittable* Hittable = Cast<IHittable>(Hit.Actor);
		if (Hittable)
		{
			Hittable->Hit(this);
		}

		if (!bCloseRangeHit)
		{
			SpawnExplosionParticleAt(TraceEndRegular);
		}
	}
	else
	{
		if (!bIsUpgraded)
		{
			SpawnExplosionParticleAt(TraceEndRegular);
		}
		else
		{
			SpawnExplosionParticleAt(TraceEndRegular);
			SpawnExplosionParticleAt(TraceEndUpgraded);
			
		}
			
	}

	

	//DrawDebugLine(GetWorld(), GetActorLocation(), FinalTraceEnd, FColor::Blue, false, 3, 0, 3);
}

void ABomb::SpawnExplosionParticleAt(FVector SpawnLocation)
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString::Printf(TEXT("spawn loc: %s"), *SpawnLocation.ToString())); }

	if (ExplosionParticle)
	{
		FVector ParticleSpawnLocation = SpawnLocation - GetActorForwardVector() * 50; // Offset because this specific particle system doesn't spawn where it should
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, ParticleSpawnLocation, FRotator(0.f), FVector(0.1), false);
		//DrawDebugSphere(GetWorld(), SpawnLocation, 25, 8, FColor::Red, false, 2);
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

