// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "Components\InputComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\PlayerController.h"
#include "EngineUtils.h"
#include "Components\CapsuleComponent.h"

#include "TopDownCamera.h"
#include "Items\Bomb.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
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

	GetCapsuleComponent()->SetCapsuleHalfHeight(12);
	GetCapsuleComponent()->SetCapsuleRadius(12);
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
	
	
	FVector SpawnLocation = GetActorLocation(); // TODO: Adjust to be placed on a tile
	NumBombs--;
	ABomb* Actor = World->SpawnActor<ABomb>(BombClass, SpawnLocation, FRotator(0.f));

	Actor->OnBombExploded.AddDynamic(this, &APlayerCharacter::OnBombExploded);


}

void APlayerCharacter::OnBombExploded()
{
	NumBombs++;
}

