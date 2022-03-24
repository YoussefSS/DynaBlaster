// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bomb.h"

#include "Components\BoxComponent.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

#include "DynaBlaster/Public/Interfaces\Hittable.h"
// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetBoxExtent(FVector(50));

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
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

	OnBombExploded.Broadcast();
	Destroy();
}

void ABomb::ExplodeOnTraceAxis(FVector AxisToTraceOn)
{
	FVector TraceEnd = GetActorLocation();
	if (!bIsUpgraded)
		TraceEnd += AxisToTraceOn * TraceLength;
	else
		TraceEnd += AxisToTraceOn * UpgradedTraceLength;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), TraceEnd, ECC_Visibility, QueryParams)) // Single as we only need to destroy the first hittable we touch
	{
		IHittable* Hittable = Cast<IHittable>(Hit.Actor);
		if (Hittable)
		{
			Hittable->Hit(this);
		}
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, FColor::Blue, false, 3, 0, 3);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

