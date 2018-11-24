// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnEntity.h"
#include "Components/TurnMovement.h"


// Sets default values
ATurnEntity::ATurnEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Movement = CreateDefaultSubobject<UTurnMovement>(FName("EntityMovement"));
    TurnOrder = 0;
}

// Called when the game starts or when spawned
void ATurnEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnEntity::StartTurn()
{
    Movement->RestoreMoves();
}

void ATurnEntity::EndTurn()
{
    Movement->Moves.Remaining = 0;
}

void ATurnEntity::SetTurnOrder(const uint32 Set)
{
    TurnOrder = Set;
}

const uint32 ATurnEntity::GetTurnOrder() const
{
    return TurnOrder;
}

void ATurnEntity::InitMovement(const FGameStats &InitNumMoves)
{
    Movement->Moves.Remaining = InitNumMoves.Remaining;
    Movement->Moves.Maximum = InitNumMoves.Maximum;
}

const uint32 ATurnEntity::GetRemainingMoves() const
{
    return Movement->Moves.Remaining;
}

const uint32 ATurnEntity::GetMaxMoves() const
{
    return Movement->Moves.Maximum;
}


const bool ATurnEntity::HasFinishMoving() const
{
    return Movement->Moves.Remaining == 0 ? true:false;
}
