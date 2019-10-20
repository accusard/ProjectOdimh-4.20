// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ActionTurnBasedComponent.h"
#include "GameTypes.h"
#include "Entities/Game/ParticipantTurn.h"


// Sets default values for this component's properties
UActionTurnBasedComponent::UActionTurnBasedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    ActionCount = FGameStats(INIT_MAX_ACTIONS,INIT_MAX_ACTIONS);
}

void UActionTurnBasedComponent::Init(const FGameStats& InitNumActions)
{
    ActionCount = InitNumActions;
}

const bool UActionTurnBasedComponent::TryExecute(const FMatch3GameAction& Action)
{
    if(ActionCount.Remaining >= Action.Cost)
    {
        LastActionCommitted = Action;
        ConsumeActionCount(Action.Cost);
        return true;
    }
    
    return false;
}

void UActionTurnBasedComponent::ResetActions()
{
    RestoreActionMax();
}

void UActionTurnBasedComponent::ConsumeActionCount(const int32 Amount)
{
    if(Amount < 0)
        return;
    
    ActionCount.Remaining -= Amount;
    
    ActionCount.Remaining = FMath::Clamp<uint32>(ActionCount.Remaining, 0, ActionCount.Maximum);
}

void UActionTurnBasedComponent::RestoreActionMax()
{
    ActionCount.Remaining = ActionCount.Maximum;
}

// Called when the game starts
void UActionTurnBasedComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

const int32 UActionTurnBasedComponent::GetRemainingActions() const
{
    return ActionCount.Remaining;
}

