// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"



// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    TurnOrder = 0;
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnParticipant::StartTurn()
{
    
}

void ATurnParticipant::EndTurn()
{
    
}

void ATurnParticipant::SetTurnOrder(const uint32 Set)
{
    TurnOrder = Set;
}

const uint32 ATurnParticipant::GetTurnOrder() const
{
    return TurnOrder;
}

void ATurnParticipant::InitMovement(const FGameStats &InitNumMoves)
{
    MaxNumMoves = InitNumMoves.Maximum;
}

const uint32 ATurnParticipant::GetMaxMoves() const
{
    return MaxNumMoves;
}
