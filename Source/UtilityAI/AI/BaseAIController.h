// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "Public/TimerManager.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

	ABaseAIController();

	void BeginPlay();

	UPROPERTY(EditDefaultsOnly, Category = "AISettings")
	float ChoseActionTime = 1.f;

	UFUNCTION()
	void ChoseAction();
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBCDecisionMaker* DecisionMaker;

	void OnPossess(APawn * InPawn) override;

	FTimerHandle ChoseActionTimerHandle;
	FTimerDelegate ChoseActionTimerDel;

};
