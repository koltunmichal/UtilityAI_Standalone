// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "WorldState.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class UTILITYAI_API UWorldState : public UObject
{
	GENERATED_BODY()

public:
	UWorldState();
	~UWorldState();
};
