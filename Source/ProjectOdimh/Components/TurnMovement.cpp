// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnMovement.h"
#include "Gametypes.h"


// Sets default values for this component's properties
UTurnMovement::UTurnMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    Moves = FGameStats(INIT_MAX_MOVES);
}

const uint32 UTurnMovement::GetRemainingMoves() const
{
    return Moves.Remaining;
}

const uint32 UTurnMovement::GetMaxMoves() const
{
    return Moves.Maximum;
}

void UTurnMovement::ConsumeMoves(const int32 Amount)
{
    if(Amount < 0)
        return;
    
    Moves.Remaining -= Amount;
    
    Moves.Remaining = FMath::Clamp(Amount, 0, INIT_MAX_MOVES);
}

void UTurnMovement::RestoreMoves()
{
    Moves.Remaining = Moves.Maximum;
    
}

// Called when the game starts
void UTurnMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

