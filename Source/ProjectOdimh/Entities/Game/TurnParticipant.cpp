// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"



// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    QueuePosition = 1;
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

void ATurnParticipant::SetQueuePosition(const uint32 Set)
{
    QueuePosition = Set;
}

const uint32 ATurnParticipant::GetQueuePosition() const
{
    return QueuePosition;
}

void ATurnParticipant::InitNumActions(const FGameStats &NumActions)
{
    MaxNumActions = NumActions.Maximum;
}

const uint32 ATurnParticipant::GetMaxNumActions() const
{
    return MaxNumActions;
}
