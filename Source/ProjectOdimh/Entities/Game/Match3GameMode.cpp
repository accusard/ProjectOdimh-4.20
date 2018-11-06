// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Queue.h"
#include "Entities/Game/TurnEntity.h"
#include "Events/GameEvent.h"


#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "DebuggerInfo.h"
#endif

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    
    TurnQueue = CreateDefaultSubobject<AQueue>("Turn Queue");
}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize the event handler list
    Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->InitEventHandlersList(GetWorld());
}

void AMatch3GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    

}

void AMatch3GameMode::Save(USaveGame* Data)
{
    // store the number of elements in TurnQueue
    
    // loop and cycle through for that many number
    
        // create a new struct for each cycle
}

const bool AMatch3GameMode::Load(USaveGame* Data)
{
    
    return true;
}

AGrid* AMatch3GameMode::GetGrid()
{
    return Grid;
}

void AMatch3GameMode::SetGrid(AGrid* Board)
{
    Grid = Board;
}

AQueue* AMatch3GameMode::GetTurnQueue()
{
    return TurnQueue;
}

void AMatch3GameMode::AddScore(const int32 Score)
{
    GameScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return GameScore;
}

void AMatch3GameMode::SetGameScore(const int32 Score)
{
    GameScore = Score;
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();

    
}

void AMatch3GameMode::SaveAndQuit()
{
    Cast<UPOdimhGameInstance>(GetGameInstance())->SaveGame(CONTINUE_GAME_SLOT);
    Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->Create(NewObject<UGameQuit>(this));
}

void AMatch3GameMode::InitTurnQueue(TArray<UObject*> QueList)
{
    for(UObject* Entity : QueList)
    {
        GetTurnQueue()->AddToList(Entity);
    }
}















