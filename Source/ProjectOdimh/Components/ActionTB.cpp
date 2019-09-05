// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ActionTB.h"
#include "Gametypes.h"


// Sets default values for this component's properties
UActionTB::UActionTB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    InitActionsPerTurn(INIT_MAX_MOVES);
}

void UActionTB::InitActionsPerTurn(const uint32 Max)
{
    ActionCount = FGameStats(Max,Max);
}

void UActionTB::Consume(const int32 Amount)
{
    if(Amount < 0)
        return;
    
    ActionCount.Remaining -= Amount;
    
    ActionCount.Remaining = FMath::Clamp<uint32>(ActionCount.Remaining, 0, ActionCount.Maximum);
}

void UActionTB::Restore()
{
    ActionCount.Remaining = ActionCount.Maximum;
    
}

// Called when the game starts
void UActionTB::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

