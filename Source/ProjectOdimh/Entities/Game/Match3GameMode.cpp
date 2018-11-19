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
    {
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("Cannot save empty TurnQueue"));
#endif
        return;
    }
    if(UPOdimhSaveGame* NewData = Cast<UPOdimhSaveGame>(Data))
    {
        // store a temporarily head actor of the current entity
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
            if(ATurnEntity* CurrentEntity = Cast<ATurnEntity>(TurnQueue->GetActiveEntity()))
            {
                // gather the information
                FGameStats MoveStats = FGameStats(CurrentEntity->GetMaxMoves(), CurrentEntity->GetRemainingMoves());
                
                // create a new struct
                FTurnEntitySaveData EntitySaveData = FTurnEntitySaveData(CurrentEntity->GetName(),
                                                             TurnQueue->Position,
                                                             MoveStats);
                // add to save data
                NewData->QueueList.Add(EntitySaveData);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
#endif
            }
            // if the next cycle is the head actor, break the loop
            if(TempHead == TurnQueue->CycleNext())
            {
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Finish saving TurnQueue when cycle reach TempHead: %s"),*TempHead->GetName());
                UE_LOG(LogTemp,Warning,TEXT("Number of entities recorded to SaveData: %i"),EntitiesRecorded);
#endif
                break;
            }
        }
    }
}

const bool AMatch3GameMode::Load(USaveGame* Data)
{
    if(!LoadQueueListFromSave(Data))
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating a new queue list."));
        TurnQueue->CreateFromNames();
        return false;
    }
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

const bool AMatch3GameMode::LoadQueueListFromSave(USaveGame* Data)
{
    // load from data
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        if(SaveData->QueueList.Num() == 0)
        {
            return false;
        }
        else
        {
            for(auto Entity : SaveData->QueueList)
            {
                FName Name = FName(*Entity.ActorID);
                uint32 Pos = Entity.PositionInQueue;
                FGameStats Moves = Entity.NumberOfMoves;
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading entity: %s, %i, %i, %i"),*Entity.ActorID,Pos,Moves.Remaining,Moves.Maximum);
#endif
                UObject* NewEntity = TurnQueue->CreateTurnEntity(Name, Pos, Moves);
                TurnQueue->AddToList(NewEntity);
            }
            return true;
        }
    }
    else return false;
}













