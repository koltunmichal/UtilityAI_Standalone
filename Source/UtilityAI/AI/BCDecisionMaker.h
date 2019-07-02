// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrainComponent.h"
#include "AIAction.h"
#include "ConsiderationTemplate.h"
#include "BCDecisionMaker.generated.h"


USTRUCT(BlueprintType)
struct FActionPackage
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionPackage")
	float MaxWeight = 0;

	UPROPERTY(BlueprintReadWrite, Instanced, EditAnywhere, Category = "ActionPackage")
	TArray<UAIAction*> PossibleActions;

	float GetMaxWeight()
	{
		float FinalWeight = 0;
		for (auto & Action : PossibleActions)
		{
			auto tempWeight = Action->Weight;
			FinalWeight = (tempWeight > FinalWeight) ? tempWeight : FinalWeight;
		}
		return FinalWeight;
	}

};

/**
 * Main AI Utility Component, Iterates over possible actions, scores them and chooses the best action
 */
UCLASS(Blueprintable, ClassGroup = AI, meta = (BlueprintSpawnableComponent))
class UTILITYAI_API UBCDecisionMaker : public UBrainComponent
{
	GENERATED_BODY()

	UBCDecisionMaker();

public:

	//Stores Information about current State of AI
	FActionContext CurrentContext = FActionContext(GetAIOwner());

	//Stores all Action Packages available for AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionPackage")
	TArray<FActionPackage> ActionPackages;

	//Stores history of past best Action, important for CurrentContext
	TArray<UAIAction*> PastActions;

	void UpdateContext(AActor* Target);

	void GetAllActionsScore();

	TSubclassOf<UGameplayAbility> GetMaxScoredAction();

	//Get Action based on it position in ActionPackages
	UAIAction* GetAction(FVector2D ActionID);

	UFUNCTION(BlueprintCallable)
	void SetPackages(UPARAM(ref) TArray<FActionPackage>& ActionPackagesRef);

private:
	//Scores Single Action
	float Score(FActionContext &ActionContext, float Bonus, float MinRelevantScore) const;

	float GetBonus(UAIAction* Actions);

	bool CheckAllRequirements(TArray<FTagRequirements>& RefToTagRequirements) const;
	bool CheckTagRequirement(FTagRequirements& RefToTagRequirement) const;

	//Stores all scores after given scoring, not used in current code
	TMap<float, FVector2D> Scores;

	// Stores pointer to best action after scoring
	UAIAction* TopAction = nullptr;

};
