// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombTrace.generated.h"

UCLASS()
class DYNABLASTER_API ABombTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Bomb Trace")
	class UBoxComponent* BoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayExplosionParticle();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomb Trace")
	UParticleSystem* ExplosionParticle;

	FTimerHandle BombTraceTimer;

	/** How long should this actor stay in the scene
	This should be the same time as the explosion visual effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bomb Trace")
	float TraceLifetime = 1.5;

	void RemoveTrace();

private:

	class UParticleSystemComponent* CurrentActivePSC;

protected:

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
