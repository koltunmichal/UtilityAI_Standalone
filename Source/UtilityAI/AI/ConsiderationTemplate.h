// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Curves/CurveFloat.h"
#include "ConsiderationTemplate.generated.h"

USTRUCT(BlueprintType)
struct FActionContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Context")
	class UAIAction* OwnerAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Context")
	class AAIController* AskingPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Context")
	AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Context")
	TArray<class UAIAction*> ContextActions;

	FActionContext()
	{
		OwnerAction = nullptr;

		AskingPawn = nullptr;

		Target = nullptr;
	}

	FActionContext(AAIController* OwnerPawn)
	{
		AskingPawn = OwnerPawn;

		OwnerAction = nullptr;

		Target = nullptr;
	}

};



/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UTILITYAI_API UConsiderationTemplate : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base")
	FString Comment = "Default Comment";

	//Curve params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base")
	UCurveFloat* Curve = nullptr;

	//Use to customize consideration input and normalization
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base Values")
		float Value = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base Values")
		float NonNormalValue = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consideration Base Values")
		float NormFactor = 0;

		UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Consideration Base Values")
		FActionContext ActionContext;

	// Scoring Functions, Currently implemented in Blueprints

		// Function getting initial input value, ultimately from MetaAI, currently from ActionContexRef
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float GetInputValue(UPARAM(ref) FActionContext &ActionContexRef) const;
		virtual float GetInputValue_Implementation(UPARAM(ref) FActionContext &ActionContexRef) const;

		// Function normalizing initial input value to value between (0,1) base on the Consideration Base Values
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float SetNormValues(float NonNormalVal) const;
		virtual float SetNormValues_Implementation(float NonNormalVal) const;
		
		// Pass the normalized input to curve, clamp results to (0,1)
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float Score(float InputValue, UPARAM(ref) FActionContext &ActionContexRef) const;
		virtual float Score_Implementation(float InputValue, UPARAM(ref) FActionContext &ActionContexRef) const;
	
};
