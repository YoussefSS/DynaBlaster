// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DynaCharacter.h"

#include "GameFramework\CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"

// Sets default values
ADynaCharacter::ADynaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BasicStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasicStaticMesh"));
	BasicStaticMesh->SetupAttachment(GetRootComponent());

	BasicStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BasicStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BasicStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetCharacterMovement()->MaxStepHeight = 1;
	GetCharacterMovement()->MaxWalkSpeed = 120;

	GetCapsuleComponent()->SetCapsuleHalfHeight(12.3);
	GetCapsuleComponent()->SetCapsuleRadius(12.3);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ADynaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADynaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

