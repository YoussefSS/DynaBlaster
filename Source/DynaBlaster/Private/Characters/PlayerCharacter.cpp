// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "Components\InputComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\PlayerController.h"
#include "EngineUtils.h"
#include "Components\CapsuleComponent.h"
#include "Kismet\GameplayStatics.h"

#include "TopDownCamera.h"
#include "Items\Bomb.h"
#include "DynaBlaster/DynaBlasterGameModeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	UWorld* World = GetWorld();
	if (PC && World)
	{
		for (TActorIterator<ATopDownCamera> CameraItr(World); CameraItr; ++CameraItr)
		{
			PC->SetViewTarget(*CameraItr);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("SpawnBomb", EInputEvent::IE_Pressed, this, &APlayerCharacter::SpawnBomb);
}

void APlayerCharacter::Hit(AActor* OtherActor)
{
	if (DeathMaterial)
	{
		BasicStaticMesh->SetMaterial(0, DeathMaterial);
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
	}

	if (GetDynaBlasterGameModeBase())
	{
		GetDynaBlasterGameModeBase()->RestartLevel();
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	GetCharacterMovement()->AddInputVector(FVector(Value, 0, 0));
}

void APlayerCharacter::MoveRight(float Value)
{
	GetCharacterMovement()->AddInputVector(FVector(0, Value, 0));
}

void APlayerCharacter::SpawnBomb()
{
	if (!ensureMsgf(BombClass != nullptr, TEXT("BombClass not set"))) return;
	if (NumBombs <= 0) return;

	UWorld* World = GetWorld();
	if (!World) return;
	
	FVector SpawnLocation = GetActorLocation();
	if (GetDynaBlasterGameModeBase())
	{
		SpawnLocation = GetDynaBlasterGameModeBase()->GetLocationOnTileMap(SpawnLocation);
	}

	NumBombs--;

	ABomb* SpawnedBomb = World->SpawnActor<ABomb>(BombClass, SpawnLocation, FRotator(0.f));
	SpawnedBomb->SetIsUpgraded(bIsBombUpgraded);
	SpawnedBomb->OnBombExploded.AddDynamic(this, &APlayerCharacter::OnBombExploded);


}

void APlayerCharacter::OnBombExploded()
{
	NumBombs++;
}

ADynaBlasterGameModeBase* APlayerCharacter::GetDynaBlasterGameModeBase()
{
	if (DynaBlasterGameMode) return DynaBlasterGameMode;

	DynaBlasterGameMode = Cast<ADynaBlasterGameModeBase>(UGameplayStatics::GetGameMode(this));

	return DynaBlasterGameMode;

}

