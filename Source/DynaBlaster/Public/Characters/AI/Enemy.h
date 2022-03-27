// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DynaBlaster/Public/Characters/DynaCharacter.h"
#include "DynaBlaster/Public/Interfaces\Hittable.h"
#include "Enemy.generated.h"

UCLASS()
class DYNABLASTER_API AEnemy : public ADynaCharacter, public IHittable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Hit(AActor* OtherActor) override;

	virtual void DestroyHelper() override;

protected:

	FVector ChooseNewRandomDirection();

	FVector CurrentDirection;

	/** Returns true if the trace hits something in the current direction */
	bool TraceInCurrentDirection();

	/** How many times should a trace be done this frame in case a new direction is not found
	* Useful so that the enemy doesn't get stuck for a while looking for a new direction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	int32 TraceAttemptsPerFrame = 5;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle DeathTimerHandle;

	/** How long before this enemy is destroyed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	float TimeToDie = 1.2;

private:

	int32 CurrentTraceAttempts = 0;

	bool bIsDying = false;
};
