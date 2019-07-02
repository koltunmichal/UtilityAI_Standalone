// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AI/AIEnemy.h"
#include "AI/UtilityAIActionsComponent.h"
#include "BCDecisionMaker.h"

ABaseAIController::ABaseAIController()
{
	//Add Decision Makerand set it to be  replicated
	DecisionMaker = CreateDefaultSubobject<UBCDecisionMaker>(TEXT("DecisionMaker "));
	DecisionMaker->SetIsReplicated(true);
	DecisionMaker->RegisterComponent();
}

void ABaseAIController::ChoseAction()
{
	AAIEnemy* Enemy = Cast<AAIEnemy>(GetPawn());
	if (Enemy)
	{
		DecisionMaker->GetAllActionsScore();
		auto BestAction = DecisionMaker->GetMaxScoredAction();
		Enemy->GetAbilitySystemComponent()->TryActivateAbilityByClass(BestAction);
	}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	if (DecisionMaker)
	{
		DecisionMaker->CurrentContext.AskingPawn = this;
	}
}

void ABaseAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	auto Enemy = Cast<AAIEnemy>(InPawn);
	if (Enemy)
	{
		DecisionMaker->SetPackages(Enemy->AIActions->GetActionPackages());
		ChoseActionTimerDel.BindUFunction(this, FName("ChoseAction"));
		GetWorld()->GetTimerManager().SetTimer(ChoseActionTimerHandle, ChoseActionTimerDel, ChoseActionTime, true);
	}
}

