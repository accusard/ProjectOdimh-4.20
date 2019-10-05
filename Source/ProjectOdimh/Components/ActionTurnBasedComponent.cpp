// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ActionTurnBasedComponent.h"
#include "Gametypes.h"
#include "GameFramework/GameMode.h"
#include "Events/GameEvent.h"


// Sets default values for this component's properties
UActionTurnBasedComponent::UActionTurnBasedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    Turn = CreateDefaultSubobject<UGameEvent>("Game Turn");
    ActionCount = FGameStats(INIT_MAX_ACTIONS,INIT_MAX_ACTIONS);
}

void UActionTurnBasedComponent::Init(AGameModeBase* SetMode, const FGameStats& InitNumActions)
{
    Turn->Init();
    GameMode = SetMode;
    ActionCount = InitNumActions;
}

const bool UActionTurnBasedComponent::TryAct(const int32 NumOfMoves)
{
    const bool bTurnNotEnded = IsTurnPending();
    
    if(bTurnNotEnded && ActionCount.Remaining >= NumOfMoves)
    {
        ConsumeAction(NumOfMoves);
        return true;
    }
    else
        return false;
}

void UActionTurnBasedComponent::OnActionsDepleted()
{
    Turn->End();
}

const bool UActionTurnBasedComponent::IsTurnPending() const
{
    return Turn->IsPendingFinish();
}

void UActionTurnBasedComponent::ResetActions()
{
    RestoreActionMax();
    Turn->ResetEvent();
}

void UActionTurnBasedComponent::ConsumeAction(const int32 Amount)
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

