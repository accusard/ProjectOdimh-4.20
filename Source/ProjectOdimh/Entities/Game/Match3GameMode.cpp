// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Queue.h"
#include "Entities/Game/TurnParticipant.h"
#include "Components/TurnMovement.h"
#include "Events/GameEvent.h"


#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "DebuggerInfo.h"
#endif

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    
    bNewGame = false;
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

void AMatch3GameMode::NotifySave(USaveGame* DataPtr)
{
    if(OrderQueuePtr == nullptr || OrderQueuePtr->GetNum() == 0) return;
    
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(DataPtr))
    {
        // store a temporarily head actor of the current entity
        UObject* HeadOfQueue = OrderQueuePtr->GetActiveEntity();
        const int32 NumOfEntities = OrderQueuePtr->GetNum();
        
#if !UE_BUILD_SHIPPING
        uint32 EntitiesRecorded = 0;
#endif
        // loop and cycle through for each element
        for(int i = 0; i <= NumOfEntities; i++)
        {
            if(ATurnParticipant* CurrentEntity = Cast<ATurnParticipant>(OrderQueuePtr->GetActiveEntity()))
            {
                // gather the information
                FGameStats MoveStats(CurrentEntity->GetMaxMoves(), CurrentEntity->GetMaxMoves());
                
                // create a new struct
                FTurnParticipantSaveData NewSaveData(CurrentEntity->GetName(),
                                                   OrderQueuePtr->CurrentIndex,
                                                   MoveStats);
                
                // add to save data
                SaveData->QueueList.Add(NewSaveData);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
                UE_LOG(LogTemp,Warning,TEXT("Saving TurnParticipant: %s, TO QUEUE POSITION: %i, REMAININGMOVES: %i, MAXMOVES: %i"), *NewSaveData.ActorID,NewSaveData.PositionInQueue,
                       NewSaveData.NumberOfMoves.Remaining, NewSaveData.NumberOfMoves.Maximum);
#endif
            }
            // if the next cycle is the head actor, break the loop
            if(HeadOfQueue == OrderQueuePtr->CycleNext())
            {
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("OrderQueuePtr contain (%i) entities; data saved (%i) entities."), NumOfEntities, EntitiesRecorded);
                UE_LOG(LogTemp,Warning,TEXT(""));
#endif
                break;
            }
        }
    }
}

const bool AMatch3GameMode::NotifyLoad(USaveGame* Data)
{
    if(!IsNewGame())
        return LoadQueueListFromSave(Data);
    
    return false;
}

const bool AMatch3GameMode::IsNewGame() const
{
    return bNewGame;
}

void AMatch3GameMode::SetNewGameState(const bool IsNewGame)
{
    bNewGame = IsNewGame;
}

AGrid* AMatch3GameMode::GetGrid()
{
    return Grid;
}

void AMatch3GameMode::SetGrid(AGrid* Board)
{
    Grid = Board;
}

ATurnBasedQueue* AMatch3GameMode::GetOrderQueue()
{
    return OrderQueuePtr;
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

    if(OrderQueueBP)
        OrderQueuePtr = Cast<ATurnBasedQueue>(GetWorld()->SpawnActor(OrderQueueBP));
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    Cast<UPOdimhGameInstance>(GetGameInstance())->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
    Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->Create(NewObject<UGameQuit>(this));
    
    SetNewGameState(false);
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
        else if(OrderQueuePtr)
        {
            for(int32 i = 0; i < SaveData->QueueList.Num(); ++i)
            {
                FString Name = SaveData->QueueList[i].ActorID;
                uint32 Pos = SaveData->QueueList[i].PositionInQueue;
                FGameStats Moves = SaveData->QueueList[i].NumberOfMoves;
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading entity: %s, %i, %i, %i"),*Name,Pos,Moves.Remaining,Moves.Maximum);
#endif
                UObject* NewEntity = OrderQueuePtr->CreateTurnParticipant(*Name, Pos, Moves);
                OrderQueuePtr->AddToList(NewEntity);
            }
            return true;
        }
    }
    return false;
}













