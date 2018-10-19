// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "AbilityComponent.h"
#include "Entities/Abilities/Ability.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    bIndestructible = false;
}

const bool UAbilityComponent::TryDestroy(UAbility* Ability)
{
    if(bIndestructible && !Ability)
        return false;
    
    return true;
}

// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

