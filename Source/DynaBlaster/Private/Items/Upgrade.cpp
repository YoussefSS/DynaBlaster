// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Upgrade.h"

#include "Components\BoxComponent.h"

#include "DynaBlaster\Public\Characters\PlayerCharacter.h"

AUpgrade::AUpgrade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AUpgrade::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AUpgrade::OnBoxBeginOverlap);
}

void AUpgrade::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OtherActor);

	if (PlayerChar)
	{
		PlayerChar->UpgradeBomb();
		Destroy();
	}
}
