// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbility.h"
#include "AIEnemy.generated.h"

UCLASS()
class UTILITYAI_API AAIEnemy : public ABaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UUtilityAIActionsComponent* AIActions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAttributeSet* AttributeSet;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override //We add this function, overriding it from IAbilitySystemInterface.
	{
		return AbilitySystemComponent;
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void PossessedBy(AController * NewController) override;

	class ABaseAIController* OwnerAI;

	void AddGPAbilities(TSubclassOf<UGameplayAbility> AbilityToAdd);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TArray<TSubclassOf<class UGameplayAbility>> KnowAbilities;

	UFUNCTION(BlueprintCallable)
	void SetAbilities(class ABaseAIController* OwnerAIRef);

};
