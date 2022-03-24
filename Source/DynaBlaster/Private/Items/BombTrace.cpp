// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BombTrace.h"

#include "Kismet\GameplayStatics.h"
#include "TimerManager.h"
#include "Particles\ParticleSystemComponent.h"
#include "Components\BoxComponent.h"

#include "DynaBlaster/Public/Interfaces\Hittable.h"
// Sets default values
ABombTrace::ABombTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetBoxExtent(FVector(50));

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ABombTrace::BeginPlay()
{
	Super::BeginPlay();
	
	PlayExplosionParticle();

	GetWorldTimerManager().SetTimer(BombTraceTimer, this, &ABombTrace::RemoveTrace, TraceLifetime);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABombTrace::OnBoxBeginOverlap);
}

// Called every frame
void ABombTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombTrace::PlayExplosionParticle()
{
	if (ExplosionParticle)
	{
		FVector ParticleSpawnLocation = GetActorLocation() - GetActorForwardVector() * 50; // Offset because this specific particle system doesn't spawn where it should
		CurrentActivePSC = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, ParticleSpawnLocation, FRotator(0.f), FVector(0.1), false);
	}
}

void ABombTrace::RemoveTrace()
{
	if (CurrentActivePSC)
	{
		CurrentActivePSC->DeactivateImmediate();
	}
	Destroy();
}

void ABombTrace::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IHittable* Hittable = Cast<IHittable>(OtherActor);

	if (Hittable)
	{
		Hittable->Hit(this);
	}
}

