// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameInstance.h"
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
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorReleased.AddUniqueDynamic(this, &ATurnParticipant::ReceiveActorReleasedNotification);
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

void ATurnParticipant::ReceiveActorReleasedNotification(AGameModeBase* Mode, AActor* ReleasedActor)
{
    if(ATile* Tile = Cast<ATile>(ReleasedActor))
    {
        if(AMatch3GameMode* Match3 = Cast<AMatch3GameMode>(Mode))
            Match3->ReceiveRequestToEndTurn(this, Tile);
    }
}

void ATurnParticipant::EndTurn()
{
    if(GridController)
    {
        GridController->UnPossess();
        Turn->End();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TODO: %s need ref to GridController to allow unpossess, and to allow the next participant to take control of the grid."), *GetName());
        Reset();
    }
}

const bool ATurnParticipant::IsTurnPending() const
{
    return Turn->IsPendingFinish();
}

void ATurnParticipant::Execute(const FMatch3GameAction& Action)
{
    if(IsTurnPending() && ActionComponent->TryExecute(Action))
    {
        
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Not enough ActionCount to execute %s Action."),  *Action.Identifier.ToString());
    
    if(GetRemainingActions() == 0)
        NotifyActionsDepleted(Action.GameMode, false);
}

const uint32 ATurnParticipant::GetRemainingActions() const
{
    return GetActionComponent()->ActionCount.Remaining;
}

UActionTurnBasedComponent* ATurnParticipant::GetActionComponent() const
{
    return ActionComponent;
}

void ATurnParticipant::NotifyActionsDepleted(AGameModeBase* Mode, const bool bSkipNotifyGameModeOfEndTurn)
{
    if(bSkipNotifyGameModeOfEndTurn)
    {
        EndTurn();
        return;
    }
    
    if(AMatch3GameMode* Match3 = Cast<AMatch3GameMode>(Mode))
        Match3->ReceiveRequestToEndTurn(this);
    
}
