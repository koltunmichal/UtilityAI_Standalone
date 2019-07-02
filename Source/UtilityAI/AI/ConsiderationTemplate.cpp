// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsiderationTemplate.h"

float UConsiderationTemplate::GetInputValue_Implementation(UPARAM(ref) FActionContext &ActionContexRef) const
{
	return 0.f;
}


float UConsiderationTemplate::SetNormValues_Implementation(float NonNormalVal) const
{
	return 0.f;
}


float UConsiderationTemplate::Score_Implementation(float InputValue, UPARAM(ref) FActionContext &ActionContexRef) const
{
	// Get initial input value
	auto TempValue = GetInputValue(ActionContexRef);
	// Normalize based on the Consideration Base Values
	TempValue = SetNormValues(TempValue);
	// Get final score based on the scoring curve
	TempValue = FMath::Clamp(Curve->GetFloatValue(TempValue), 0.0f, 1.0f);
	return TempValue;
}