// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Entities/Game/Match3GameMode.h"
#include "Events/GameEvent.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Turn = CreateDefaultSubobject<UGameEvent>("Game Turn");
}

void ATurnParticipant::Init(const uint32 TurnPosition,  AGameModeBase* SetGameMode, const FGameStats &SetNumActions)
{
    SetQueuePosition(TurnPosition);
    GameMode = Cast<AMatch3GameMode>(SetGameMode);
    InitNumActions(SetNumActions);
}

void ATurnParticipant::Reset()
{
    Turn->Reset();
    NumActions.Remaining = NumActions.Maximum;
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
    
    if(!GameMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("Game mode have not been set for %s."), *GetName());
        return;
    }
    
    GameMode->GetGameState<APOdimhGameState>()->TurnCounter++;
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
