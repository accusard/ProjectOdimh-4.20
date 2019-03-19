// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "Components/TurnMovement.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Movement = CreateDefaultSubobject<UTurnMovement>(FName("EntityMovement"));
    TurnOrder = 0;
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnParticipant::StartTurn()
{
    Movement->RestoreMoves();
}

void ATurnParticipant::EndTurn()
{
    Movement->Moves.Remaining = 0;
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
    Movement->Moves.Remaining = InitNumMoves.Remaining;
    Movement->Moves.Maximum = InitNumMoves.Maximum;
}

const uint32 ATurnParticipant::GetRemainingMoves() const
{
    return Movement->Moves.Remaining;
}

const uint32 ATurnParticipant::GetMaxMoves() const
{
    return Movement->Moves.Maximum;
}


const bool ATurnParticipant::HasFinishMoving() const
{
    return Movement->Moves.Remaining == 0 ? true:false;
}
