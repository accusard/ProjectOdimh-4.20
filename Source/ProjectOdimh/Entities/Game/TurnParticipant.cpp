// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnParticipant.h"
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

void ATurnParticipant::Init(AGameModeBase* SetGameMode, const FGameStats &SetNumActions, AController* SetController)
{
    ActionComponent->Init(SetGameMode, SetNumActions);
    AssignedController = SetController;
    DefaultPawn = SetGameMode->DefaultPawnClass.GetDefaultObject();
}

void ATurnParticipant::Reset()
{
    ActionComponent->ResetActions();
}

// Called when the game starts or when spawned
void ATurnParticipant::BeginPlay()
{
	Super::BeginPlay();
}

AController* ATurnParticipant::GetAssignedController() const
{
    return AssignedController;
}

void ATurnParticipant::StartTurn()
{
    AssignedController->Possess(DefaultPawn);
    ActionComponent->StartTurn();
}

void ATurnParticipant::EndTurn()
{
    AssignedController->UnPossess();
    ActionComponent->EndTurn();
}
