// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCamera.h"




void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();

	FadeIn();
}

void ATopDownCamera::SetCameraLocation(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}
