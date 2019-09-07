// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameInstance.h"
#include "Events/GameEvent.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
    QueuePosition = 1;
    GameTurn = CreateDefaultSubobject<UGameEvent>("Game Turn");
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
    GameTurn->Init();
}

void ATurnParticipant::StartTurn()
{
    GameTurn->Reset();
    GameTurn->Start();
}

void ATurnParticipant::EndTurn()
{
    GameTurn->End();
}

const bool ATurnParticipant::IsTurnPending() const
{
    return GameTurn->IsPendingFinish();
}

void ATurnParticipant::SetQueuePosition(const uint32 Set)
{
    QueuePosition = Set;
}

const uint32 ATurnParticipant::GetQueuePosition() const
{
    return QueuePosition;
}

void ATurnParticipant::InitNumActions(const FGameStats &MaxActions)
{
    NumActions = MaxActions;
}

const FGameStats& ATurnParticipant::GetNumActions() const
{
    return NumActions;
}

void ATurnParticipant::ConsumeAction(const uint32 Amt)
{
    NumActions.Remaining -= Amt;
    NumActions.Remaining = FMath::Clamp<uint32>(NumActions.Remaining, 0, NumActions.Maximum);
}
