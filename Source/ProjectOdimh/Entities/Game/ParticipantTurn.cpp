// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ParticipantTurn.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Entities/Game/Match3GameMode.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"


// Sets default values
AParticipantTurn::AParticipantTurn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    ActionComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Component");
   
    
}

void AParticipantTurn::Init(AGameModeBase* SetGameMode, const FGameStats &SetNumActions, AController* SetController)
{
    ActionComponent->Init(SetNumActions);
    GridController = SetController;
    
}

void AParticipantTurn::Reset()
{
    ActionComponent->ResetActions();
}

// Called when the game starts or when spawned
void AParticipantTurn::BeginPlay()
{
	Super::BeginPlay();
}

AController* AParticipantTurn::GetGridController() const
{
    return GridController;
}

void AParticipantTurn::Execute(const FMatch3GameAction& Action, UGameEvent* GameTurn)
{
    if(Action.GameMode->IsTurnPending() && ActionComponent->TryExecute(Action))
    {
        
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Not enough ActionCount to execute %s Action."),  *Action.Identifier.ToString());
    
    if(GetRemainingActions() == 0)
        NotifyActionsDepleted(Action.GameMode, GameTurn, false);
}

const uint32 AParticipantTurn::GetRemainingActions() const
{
    return GetActionComponent()->ActionCount.Remaining;
}

UActionTurnBasedComponent* AParticipantTurn::GetActionComponent() const
{
    return ActionComponent;
}

void AParticipantTurn::NotifyActionsDepleted(AGameModeBase* Mode, UGameEvent* TurnEvent, const bool bSkipRequestToEndTurn)
{
    if(AMatch3GameMode* Match3 = Cast<AMatch3GameMode>(Mode))
    {
        if(bSkipRequestToEndTurn)
        {
            Match3->EndTurn(this, TurnEvent);
            return;
        }
        
        Match3->ReceiveRequestToEndTurn(this, TurnEvent);
    }
}
