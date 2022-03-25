// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/Enemy.h"

#include "GameFramework\CharacterMovementComponent.h"
#include "Components\CapsuleComponent.h"
#include "DrawDebugHelpers.h"

#include "DynaBlaster\Public\Characters\PlayerCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 30;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaultController();
	ChooseNewRandomDirection();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCapsuleBeginOverlap);

 }

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->AddInputVector(CurrentDirection);

	while (CurrentTraceAttempts++ < TraceAttemptsPerFrame && TraceInCurrentDirection())
		ChooseNewRandomDirection();
	CurrentTraceAttempts = 0;
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Hit(AActor* OtherActor)
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString::Printf(TEXT("enemy hit"))); }
}

FVector AEnemy::ChooseNewRandomDirection()
{
	int32 Randomness = FMath::RoundToInt(FMath::FRandRange(1, 4));

	if (Randomness == 1) CurrentDirection =  GetActorRightVector();
	if (Randomness == 2) CurrentDirection =  -GetActorRightVector();
	if (Randomness == 3) CurrentDirection =  GetActorForwardVector();
	if (Randomness == 4) CurrentDirection =  -GetActorForwardVector();

	return CurrentDirection;
}

bool AEnemy::TraceInCurrentDirection()
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector TraceEnd = GetActorLocation() + CurrentDirection * GetCapsuleComponent()->GetScaledCapsuleRadius() + CurrentDirection;
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), TraceEnd, ECC_Visibility, QueryParams))
	{
		if ((&Hit.Actor) && Hit.Actor->IsA<ADynaCharacter>()) // Don't change direction if traced another character
			return false;
		else
			return true;
		
	}
	//DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, FColor::Blue, false, 0, 0, 1);

	return false;
}

void AEnemy::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OtherActor);
	if (PlayerChar)
	{
		PlayerChar->Hit(this);
	}
}

