// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ActionTurnBasedComponent.h"
#include "GameTypes.h"
#include "Entities/Game/TurnParticipant.h"


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

const bool UActionTurnBasedComponent::Execute(const FAction& Action)
{
    if(ActionCount.Remaining >= Action.Cost && Cast<ATurnParticipant>(GetOwner())->IsTurnPending())
    {
        LastActionCommitted = Action;
        ConsumeActionCount(Action.Cost);
        return true;
    }
    
    return false;
}

void UActionTurnBasedComponent::NotifyActionsDepleted()
{
    UE_LOG(LogTemp,Warning, TEXT("%s has depleted all of its action counts."), *GetOwner()->GetName());
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
    
    if(ActionCount.Remaining == 0)
        NotifyActionsDepleted();
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

