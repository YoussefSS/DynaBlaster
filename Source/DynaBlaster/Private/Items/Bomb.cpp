// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bomb.h"


#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet\GameplayStatics.h"
#include "Components\BoxComponent.h"

#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "DynaBlaster/Public/Items/BombTrace.h"
// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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

	
	SpawnBombTraceAt(GetActorLocation());

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

	// LineTrace
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
			APawn* Pawn = Cast<APawn>(Hittable);
			if (Pawn) // Still spawn a trace if the hittable is a pawn
			{
				SpawnBombTraceAt(TraceEndRegular);
			}
			Hittable->Hit(this);
		}

		if (!bCloseRangeHit)
		{
			SpawnBombTraceAt(TraceEndRegular);
		}
	}
	else
	{
		if (!bIsUpgraded)
		{
			SpawnBombTraceAt(TraceEndRegular);
		}
		else
		{
			SpawnBombTraceAt(TraceEndRegular);
			SpawnBombTraceAt(TraceEndUpgraded);
		}
			
	}

	//DrawDebugLine(GetWorld(), GetActorLocation(), FinalTraceEnd, FColor::Blue, false, 3, 0, 3);
}

void ABomb::SpawnBombTraceAt(FVector SpawnLocation)
{
	UWorld* World = GetWorld();
	if (BombTraceClass && World)
	{
		ABombTrace* Actor = World->SpawnActor<ABombTrace>(BombTraceClass, SpawnLocation, FRotator(0.f));
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

