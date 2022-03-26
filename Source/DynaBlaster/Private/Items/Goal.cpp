// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Goal.h"

#include "Components\BoxComponent.h"

#include "DynaBlaster\Public\Characters\PlayerCharacter.h"
AGoal::AGoal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AGoal::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnBoxBeginOverlap);
}

void AGoal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OtherActor);

	if (PlayerChar)
	{
		PlayerChar->Win();
	}
}