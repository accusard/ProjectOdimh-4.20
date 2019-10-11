// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameState.h"
#include "Entities/Game/Match3GameMode.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    ActionComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Component");
   
    Turn = CreateDefaultSubobject<UGameEvent>("Game Turn");
}

void ATurnParticipant::Init(AGameModeBase* SetGameMode, const FGameStats &SetNumActions, AController* SetController)
{
    ActionComponent->Init(SetNumActions);
    Turn->Init();
    GridController = SetController;
    DefaultPawn = SetGameMode->DefaultPawnClass.GetDefaultObject();
}

void ATurnParticipant::Reset()
{
    ActionComponent->ResetActions();
    Turn->ResetEvent();
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
}

AController* ATurnParticipant::GetGridController() const
{
    return GridController;
}

void ATurnParticipant::StartTurn(APOdimhGameState* State)
{
    GridController->Possess(DefaultPawn);
    State->TurnCounter++;
}

void ATurnParticipant::EndTurn()
{
    GridController->UnPossess();
    Turn->End();
}

const bool ATurnParticipant::IsTurnPending() const
{
    return Turn->IsPendingFinish();
}

void ATurnParticipant::Execute(const FAction& Action)
{
    if(GetRemainingActions() == 0)
    {
        NotifyActionsDepleted(true);
        return;
    }
    
    if(ActionComponent->TryExecute(Action))
        return;
}

const uint32 ATurnParticipant::GetRemainingActions() const
{
    return GetActionComponent()->ActionCount.Remaining;
}

UActionTurnBasedComponent* ATurnParticipant::GetActionComponent() const
{
    return ActionComponent;
}

void ATurnParticipant::NotifyActionsDepleted(const bool bEndTurnNow)
{
    if(bEndTurnNow)
        EndTurn();
    
}
