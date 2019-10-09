// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ActionTurnBasedComponent.h"
#include "GameFramework/GameMode.h"
#include "Entities/Game/TurnParticipant.h"


// Sets default values for this component's properties
UActionTurnBasedComponent::UActionTurnBasedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    ActionCount = FGameStats(INIT_MAX_ACTIONS,INIT_MAX_ACTIONS);
}

void UActionTurnBasedComponent::Init(AGameModeBase* SetMode, const FGameStats& InitNumActions)
{
    GameMode = SetMode;
    ActionCount = InitNumActions;
}

const bool UActionTurnBasedComponent::TryAct(const int32 NumOfMoves)
{
    if(ActionCount.Remaining >= NumOfMoves && Cast<ATurnParticipant>(GetOwner())->IsTurnPending())
    {
        ConsumeActionCount(NumOfMoves);
        return true;
    }
    
    return false;
}

void UActionTurnBasedComponent::NotifyActionsDepleted()
{
    
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

