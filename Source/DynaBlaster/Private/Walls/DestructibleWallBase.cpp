// Fill out your copyright notice in the Description page of Project Settings.


#include "Walls/DestructibleWallBase.h"

#include "Components\BoxComponent.h"

// Sets default values
ADestructibleWallBase::ADestructibleWallBase()
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
void ADestructibleWallBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnDestroyed.AddDynamic(this, &ADestructibleWallBase::OnWallDestroyed);
}

void ADestructibleWallBase::OnWallDestroyed(AActor* DestroyedActor)
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("destroyed"))); }
}

// Called every frame
void ADestructibleWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

