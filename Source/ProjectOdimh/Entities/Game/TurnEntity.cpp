// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnEntity.h"


// Sets default values
ATurnEntity::ATurnEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bMoveFinished = false;
    // TODO:
//    CurrentRound =
    
    // TODO: create default subobject
    // TurnMoves =
}

// Called when the game starts or when spawned
void ATurnEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnEntity::EndTurn()
{
    bMoveFinished = true;
    
    const FString HasMoved = HasFinishMoving() ? "True" : "False";
    UE_LOG(LogTemp, Warning, TEXT("%s - bMoveFinished: %s"), *GetName(), *HasMoved);
}

UTurnMovement* ATurnEntity::GetMovement() const
{
    return TurnMoves;
}

const bool ATurnEntity::HasFinishMoving() const
{
    return bMoveFinished;
}
