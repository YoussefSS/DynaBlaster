// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DYNABLASTER_API APlayerCharacter : public ACharacter, public IHittable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* BasicStaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player | Bomb")
	TSubclassOf<class ABomb> BombClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player | Bomb", meta = (ClampMin = "0"))
	int32 NumBombs = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Hit(AActor* OtherActor) override;

private:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void SpawnBomb();

	UFUNCTION()
	void OnBombExploded();
};
