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
    Turn = CreateDefaultSubobject<UGameEvent>("Game Turn");
}

void ATurnParticipant::Reset()
{
    Turn->Reset();
    
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
    Turn->Init();
}

void ATurnParticipant::StartTurn()
{
    Turn->Start();
}

void ATurnParticipant::EndTurn()
{
    Turn->End();
}

const bool ATurnParticipant::IsTurnPending() const
{
    return Turn->IsPendingFinish();
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
