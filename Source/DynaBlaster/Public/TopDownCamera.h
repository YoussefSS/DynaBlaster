// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TopDownCamera.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API ATopDownCamera : public ACameraActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/** From from black to transparent, implemented in blueprints */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeIn();

	/** From transparent to black, implemented in blueprints */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FadeOut();
};
