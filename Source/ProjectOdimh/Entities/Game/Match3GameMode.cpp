// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Queue.h"
#include "Entities/Game/TurnEntity.h"
#include "Components/TurnMovement.h"
#include "Events/GameEvent.h"


#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "DebuggerInfo.h"
#endif

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    
    TurnQueue = CreateDefaultSubobject<ATurnBasedQueue>("Turn Queue");
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
    if(TurnQueue->GetNum() == 0)
        return;
    
    if(UPOdimhSaveGame* NewData = Cast<UPOdimhSaveGame>(Data))
    {
        // store a temporarily head actor of the nextcycle
        UObject* TempHead = TurnQueue->GetActiveEntity();
        const int32 NumOfEntities = TurnQueue->GetNum();
        
#if !UE_BUILD_SHIPPING
        uint32 EntitiesRecorded = 0;
        UE_LOG(LogTemp,Warning,TEXT("Recording initial TempHead: %s"),*TempHead->GetName());
        UE_LOG(LogTemp,Warning,TEXT("Number of entities in queue: %i"),NumOfEntities);
#endif
        
        // loop and cycle through for each element
        for(int i = 0; i <= NumOfEntities; i++)
        {
            // if the current loop is the head actor, break the loop
            if(TempHead == TurnQueue->CycleNext())
            {
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Finish saving TurnQueue when cycle reach TempHead: %s"),*TempHead->GetName());
                UE_LOG(LogTemp,Warning,TEXT("Number of entities recorded to SaveData: %i"),EntitiesRecorded);
#endif
                break;
            }
            if(ATurnEntity* CurrentEntity = Cast<ATurnEntity>(TurnQueue->GetActiveEntity()))
            {
                // create a new struct for each cycle
                
                FGameStats MoveStats = FGameStats(CurrentEntity->GetMaxMoves());
                MoveStats.Remaining = CurrentEntity->GetRemainingMoves();
                
                FTurnEntityData QueueSaveData = FTurnEntityData(CurrentEntity->GetName(),
                                                             TurnQueue->Position,
                                                             MoveStats,
                                                             CurrentEntity->HasFinishMoving());
                
                // gather the information and add to Data->QueueData
                NewData->QueueList.Add(QueueSaveData);
                
//                TurnQueue->GetActiveEntity();
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
#endif
            }
        }
    }
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

ATurnBasedQueue* AMatch3GameMode::GetTurnQueue()
{
    return TurnQueue;
}

void AMatch3GameMode::AddScore(const int32 Score)
{
    CurrentScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return CurrentScore;
}

void AMatch3GameMode::SetCurrentScore(const int32 Score)
{
    CurrentScore = Score;
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















