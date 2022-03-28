// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bomb.h"


#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet\GameplayStatics.h"
#include "Components\BoxComponent.h"

#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "DynaBlaster/Public/Items/BombTrace.h"
#include "DynaBlaster\Public\Characters\PlayerCharacter.h"

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

	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABomb::ABombOnBoxEndOverlap);
}

void ABomb::Explode()
{
	if (ExplosionSFX)
	{
		UGameplayStatics::PlaySound2D(this, ExplosionSFX);
	}

	// Destroy adjacent tiles
	ExplodeOnAxis(GetActorForwardVector());
	ExplodeOnAxis(-GetActorForwardVector());
	ExplodeOnAxis(GetActorRightVector());
	ExplodeOnAxis(-GetActorRightVector());
	
	SpawnBombTraceAt(GetActorLocation());

	OnBombExploded.Broadcast();

	Destroy();
}

void ABomb::ExplodeOnAxis(FVector AxisToTraceOn)
{
	// Set trace ends
	FVector TraceEndRegular = GetActorLocation() + AxisToTraceOn * TraceLengthRegular;
	FVector TraceEndUpgraded = GetActorLocation() + AxisToTraceOn * TraceLengthUpgraded;
	FVector FinalTraceEnd;
	
	if (!bIsUpgraded)
		FinalTraceEnd = TraceEndRegular;
	else
		FinalTraceEnd = TraceEndUpgraded;

	// LineTrace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), FinalTraceEnd, ECC_Visibility, QueryParams)) // Single as we only need to destroy the first hittable we touch
	{
		// If upgraded, do another hit test with the regular trace end, if there is nothing there, spawn a particle
		FHitResult CloseHit;
		if (bIsUpgraded && !GetWorld()->LineTraceSingleByChannel(CloseHit, GetActorLocation(), TraceEndRegular, ECC_Visibility, QueryParams)) // If upgraded, spawn a particle at the regular position
		{
			SpawnBombTraceAt(TraceEndRegular);
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
	}
	else
	{
		SpawnBombTraceAt(TraceEndRegular);
		if (bIsUpgraded)
			SpawnBombTraceAt(TraceEndUpgraded);
			
	}

	//DrawDebugLine(GetWorld(), GetActorLocation(), FinalTraceEnd, FColor::Blue, false, 3, 0, 3);
}

void ABomb::SpawnBombTraceAt(FVector SpawnLocation)
{
	UWorld* World = GetWorld();
	if (BombTraceClass && World)
	{
		World->SpawnActor<ABombTrace>(BombTraceClass, SpawnLocation, FRotator(0.f));
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::ABombOnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Player shouldn't be able to walk over the bomb after placing it and moving away
	if(OtherActor->IsA<APlayerCharacter>())
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

