// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DynaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DYNABLASTER_API UDynaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	FORCEINLINE void SetNumRows(int32 NewNumRows) { NumRows = NewNumRows; }
	FORCEINLINE void SetNumColumns(int32 NewNumColumns) { NumColumns = NewNumColumns; }
	FORCEINLINE void SetNumEnemies(int32 NewNumEnemies) { NumEnemies = NewNumEnemies; }

	FORCEINLINE int32 GetNumRows() { return NumRows; }
	FORCEINLINE int32 GetNumColumns() { return NumColumns; }
	FORCEINLINE int32 GetNumEnemies() { return NumEnemies; }

private:

	int32 NumRows = 11;
	int32 NumColumns = 13;
	int32 NumEnemies = 3;
};
