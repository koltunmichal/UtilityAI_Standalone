// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsIsInRange.h"
#include "AI/BaseAIController.h"

float UConsIsInRange::GetInputValue_Implementation(UPARAM(ref) FActionContext &ActionContexRef) const
{
	auto SourceLocation = ActionContexRef.AskingPawn->GetPawn()->GetActorLocation();
	auto TargetLocation = ActionContexRef.Target->GetActorLocation();
	return FVector::Dist(SourceLocation, TargetLocation);
}

float UConsIsInRange::SetNormValues_Implementation(float NonNormalVal) const
{
	return NonNormalVal / (MinOptDistance + MaxOptDistance);
}