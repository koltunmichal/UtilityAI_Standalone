// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemy.h"
#include "UtilityAIActionsComponent.h"
#include "AbilitySystemComponent.h"
#include "BaseAIController.h"
#include "AttributeSet.h"


// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create AI Actions component that will store AI action packages, and set it to be explicitly replicated
	AIActions = CreateDefaultSubobject<UUtilityAIActionsComponent>(TEXT("AIActions"));
	AIActions->SetIsReplicated(true);
	AIActions->RegisterComponent();

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Set AI Actions, add them as Gameplay Abilities
void AAIEnemy::SetAbilities(class ABaseAIController* OwnerAIRef)
{
	if (AbilitySystemComponent)
	{
		OwnerAI = OwnerAIRef;
		AbilitySystemComponent->InitAbilityActorInfo(OwnerAI, this);

		if (AIActions)
		{
			auto ActionPackages = AIActions->GetActionPackages();
			for (auto Package : ActionPackages)
			{
				auto Actions = Package.PossibleActions;
				for (auto Action : Actions)
				{
					AddGPAbilities(Action->Task);
				}
			}
		}
	}
}

//Add Gameplay Abilities
void AAIEnemy::AddGPAbilities(TSubclassOf<UGameplayAbility> AbilityToAdd)
{
	if (HasAuthority() && AbilityToAdd)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAdd.GetDefaultObject()));
	}
}

void AAIEnemy::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
	AIActions->SetBaseActions();
	SetAbilities(Cast<ABaseAIController>(NewController));
}