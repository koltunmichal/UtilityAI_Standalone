// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "ConsiderationTemplate.h"
#include "AIAction.generated.h"



UENUM(BlueprintType)
enum class ETagSources : uint8
{
	Self,
	Target
};


UENUM(BlueprintType)
enum class ETagPrerequisites : uint8
{
	HasAnyOf,
	HasAllOf,
	HasNoneOf
};

USTRUCT(BlueprintType)
struct FTagRequirements
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETagSources TagSource = ETagSources::Self;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETagPrerequisites TagPrerequisite = ETagPrerequisites::HasAllOf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Tags;

};


/**
 * Base Class For AI Action, connects AI TASK with tag requirements and considerations
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UTILITYAI_API UAIAction : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Comment = "Default Comment";

	// AI Task To Preform, UAIAction does not store any implementation of target action
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Task;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Weight = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FTagRequirements> TagRequirements;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TArray<UConsiderationTemplate*> Considerations;

};