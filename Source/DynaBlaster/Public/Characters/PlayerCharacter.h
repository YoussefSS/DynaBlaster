// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "DynaBlaster/Public/Characters/DynaCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DYNABLASTER_API APlayerCharacter : public ADynaCharacter, public IHittable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player | Bomb")
	TSubclassOf<class ABomb> BombClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player | SFX")
	class USoundBase* WinSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player | Bomb", meta = (ClampMin = "0"))
	int32 NumBombs = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Hit(AActor* OtherActor) override;

	void UpgradeBomb() { bIsBombUpgraded = true; } // If there were more upgrades, an array of enum upgrades or something like that could be used

	void Win();

protected:

	virtual void DestroyHelper() override {}

private:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void SpawnBomb();

	void Pause();

	UFUNCTION()
	void OnBombExploded();

	class ADynaBlasterGameModeBase* DynaBlasterGameMode;

	ADynaBlasterGameModeBase* GetDynaBlasterGameModeBase();

	bool bIsBombUpgraded = false;

};
