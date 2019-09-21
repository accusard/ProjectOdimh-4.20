// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Entities/Game/Match3GameMode.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Components/GridControlComponent.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    ActionComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Component");
    GridControlComponent = CreateDefaultSubobject<UGridControlComponent>("Grid Control Component");
    
}

void ATurnParticipant::Init(const uint32 TurnPosition,  AGameModeBase* SetGameMode, const FGameStats &SetNumActions, AController* SetController)
{
    SetQueuePosition(TurnPosition);
    InitNumActions(SetNumActions);
    ActionComponent->Init(SetGameMode);
    Controller = SetController;
}

void ATurnParticipant::Reset()
{
    ActionComponent->Reset();
    NumActions.Remaining = NumActions.Maximum;
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
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
