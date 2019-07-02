// Fill out your copyright notice in the Description page of Project Settings.


#include "BCDecisionMaker.h"
#include "GameplayTagContainer.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"
#include "Engine/GameEngine.h"
#include "AIAction.h"


UBCDecisionMaker::UBCDecisionMaker()
{
}

void UBCDecisionMaker::SetPackages(UPARAM(ref) TArray<FActionPackage>& ActionPackagesRef)
{
	ActionPackages = ActionPackagesRef;
}

void UBCDecisionMaker::GetAllActionsScore()
{
	// Set initial conditions
	Scores.Empty();
	TopAction = GetAction(FVector2D(0, 0));
	float Cutoff = 0.0f;
	UpdateContext(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Decrementing loop over owned action packages
	for(int32 i = (ActionPackages.Num()-1); i >= 0; --i)
	{
		auto & ActionPackage = ActionPackages[i];
		auto & PossibleActions = ActionPackage.PossibleActions;
		// Decrementing loop over actions in package
		for (int32 j = (PossibleActions.Num()-1); j >= 0; --j)
		{
			// Get Action
			auto & Action = PossibleActions[j];
			//Check Tag Requirements, skip action if requirements are not met 
			if (!CheckAllRequirements(Action->TagRequirements)) { continue; }
			// Get Bonus Based on Context, NOT IMPLEMENTED YET
			float bonus = GetBonus(Action);
			// If Bonus is smaller than total score of top action, skip scoring of given action, as it will always have smaller score
			if (bonus < Cutoff) { continue; }
			// Set Action Context
			CurrentContext.OwnerAction = Action;
			// Score Action
			float ActionScore = Score(CurrentContext, bonus, Cutoff);
			auto ActionName = Action->GetName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Red, FString::Printf(TEXT("Score %s : %f"), *ActionName, ActionScore));
			}
				
			// Set as new Top Action if better than previous one
			if (ActionScore > Cutoff)
			{ 
				Cutoff = ActionScore; 
				TopAction = Action;
			}
			Scores.Add(ActionScore, FVector2D(i, j));

		}
	}
}

bool UBCDecisionMaker::CheckAllRequirements(TArray<FTagRequirements>& RefToTagRequirements) const
{
	for (auto & TagRequirement : RefToTagRequirements)
	{
		if (!CheckTagRequirement(TagRequirement)) { return false; }
	}
	return true;
}

bool UBCDecisionMaker::CheckTagRequirement(FTagRequirements& RefToTagRequirement) const
{
	FGameplayTagContainer ConditionTags = RefToTagRequirement.Tags;
	FGameplayTagContainer RefTags;

	//Get Reference Tags from proper source
	switch (RefToTagRequirement.TagSource)
	{
		case(ETagSources::Self):
		{
			auto AskingAI = Cast<ABaseCharacter>(CurrentContext.AskingPawn->GetPawn());
			if (!AskingAI) { return false; }
			RefTags = AskingAI->TagContainer;
			break;
		}
		case(ETagSources::Target):
		{			
			auto Target = Cast<ABaseCharacter>(CurrentContext.Target);
			if (!Target) { return false; }
			RefTags = Target->TagContainer;
			break;
		}
	}

	switch (RefToTagRequirement.TagPrerequisite)
	{
		case(ETagPrerequisites::HasAllOf):
			return RefTags.HasAllExact(ConditionTags);
			break;
		case(ETagPrerequisites::HasAnyOf):
			return RefTags.HasAnyExact(ConditionTags);
			break;
		case(ETagPrerequisites::HasNoneOf):
			return !RefTags.HasAnyExact(ConditionTags);
			break;
		default:
			return false;
	}
}

float UBCDecisionMaker::Score(FActionContext &ActionContext, float Bonus, float MinRelevantScore) const
{
	// Set initial value to bonus
	float Score = Bonus;
	// Get all considerations
	auto& Considerations = ActionContext.OwnerAction->Considerations;
	// Iterate over considerations
	for (const auto & consideration : Considerations)
	{
		// break from scoring if score was lowered to smaller value than MinRelevantScore
		if (Score < MinRelevantScore) { break; }

		//TODO Get value from MetaAI
		auto InputValue = 0;

		//Get Consideration Score
		auto CurvedInputValue = consideration->Score(InputValue, ActionContext);

		//Refresh Score
		Score *= CurvedInputValue;
	}

	return Score;
}

void UBCDecisionMaker::UpdateContext(AActor* Target)
{
	CurrentContext.ContextActions = PastActions;
	CurrentContext.Target = Target;
}

float UBCDecisionMaker::GetBonus(UAIAction* Actions)
{
	return 1;
}

TSubclassOf<UGameplayAbility> UBCDecisionMaker::GetMaxScoredAction()
{
	return TopAction ? TopAction->Task: nullptr;
}

UAIAction* UBCDecisionMaker::GetAction(FVector2D ActionID)
{
	return ActionPackages[int32(ActionID.X)].PossibleActions[int32(ActionID.Y)];
}