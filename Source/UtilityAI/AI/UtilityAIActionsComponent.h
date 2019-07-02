// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BCDecisionMaker.h"
#include "AIAction.h"
#include "UtilityAIActionsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTILITYAI_API UUtilityAIActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUtilityAIActionsComponent();

	// Array storing all possible actions 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionPackage")
	TArray<FActionPackage> ActionPackages;

	// Struct storing package with base action of given character.  
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ActionPackage")
	FActionPackage BaseActions;

	UFUNCTION(BlueprintCallable)
	void SetBaseActions();

	UFUNCTION(BlueprintCallable)
	TArray<FActionPackage>& GetActionPackages();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
};
