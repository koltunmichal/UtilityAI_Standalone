// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/ConsiderationTemplate.h"
#include "ConsIsInRange.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UConsIsInRange : public UConsiderationTemplate
{
	GENERATED_BODY()

public:
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base")
		float MinOptDistance = 50;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base")
		float MaxOptDistance = 100;

		// Function getting initial input value, ultimately from MetaAI, currently from ActionContexRef
		virtual float GetInputValue_Implementation(UPARAM(ref) FActionContext &ActionContexRef) const override;

		// Function normalizing initial input value to value between (0,1) base on the Consideration Base Values
		virtual float SetNormValues_Implementation(float NonNormalVal) const override;
};
