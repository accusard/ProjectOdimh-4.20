// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
#include "POdimhGameState.h"
#include "Entities/Game/Match3GameMode.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Components/TileHandlerComponent.h"


// Sets default values
ATurnParticipant::ATurnParticipant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    ActionComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Component");
    TileHandlerComponent = CreateDefaultSubobject<UTileHandlerComponent>("Grid Control Component");
    
}

void ATurnParticipant::Init(AGameModeBase* SetGameMode, const FGameStats &SetNumActions, AController* SetController)
{
    ActionComponent->Init(SetGameMode, SetNumActions);
    GridController = SetController;
    DefaultPawn = SetGameMode->DefaultPawnClass.GetDefaultObject();
}

void ATurnParticipant::Reset()
{
    ActionComponent->ResetActions();
    GridController->UnPossess();
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
    ActionComponent->OnActionsDepleted();
}
