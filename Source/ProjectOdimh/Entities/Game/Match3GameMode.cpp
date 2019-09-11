// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "ProjectOdimh.h"
#include "POdimhGameState.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Queue.h"
#include "Entities/Game/TurnParticipant.h"
#include "Components/ActionTB.h"
#include "Events/GameEvent.h"


#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "DebuggerInfo.h"
#endif

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    OrderQueuePtr = CreateDefaultSubobject<ATurnBasedQueue>("Order Queue");
    bNewGame = false;
}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    GetGameInstance<UPOdimhGameInstance>()->EventManager->InitEventHandlersList(GetWorld());
    GameRound = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(this, "Game Round", false);
    
    if(!TryLoadGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One))
        StartNewGame((int32)EPlayer::One);
    
    uint32 NextParticipantIndex = 0;
    StartRound(NextParticipantIndex);
}

void AMatch3GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    

}

void AMatch3GameMode::NotifySave(USaveGame* DataPtr)
{
    if(OrderQueuePtr == nullptr || OrderQueuePtr->GetNumObjectsInList() == 0) return;
    
    SaveQueueList(DataPtr);
}

const bool AMatch3GameMode::NotifyLoad(USaveGame* Data)
{
    if(LoadQueueListFromSave(Data))
        return true;
    
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
    
    
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    SetNewGameState(false);
    const bool bIgnorePlatformSpecificRestrictions = true;
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
    
    UKismetSystemLibrary::QuitGame(GetWorld(),
                                   UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex),
                                   EQuitPreference::Quit,
                                   bIgnorePlatformSpecificRestrictions);
}

const bool AMatch3GameMode::CreateQueueFromBlueprint()
{
    if(!OrderQueueBP)
    {
        UE_LOG(LogTemp,Warning,TEXT("Order queue blueprint have not been assigned."));
        return false;
    }
    
    if(OrderQueuePtr)
        OrderQueuePtr->MarkPendingKill();
    
    UE_LOG(LogTemp,Warning,TEXT("Creating a new queue list from preassigned blueprint."));
    OrderQueuePtr = Cast<ATurnBasedQueue>(GetWorld()->SpawnActor(OrderQueueBP));
    
    return true;
}

const bool AMatch3GameMode::LoadQueueListFromSave(USaveGame* Data)
{
    // load from save
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        if(SaveData->QueueList.Num() != 0)
        {
            for(int32 i = 0; i < SaveData->QueueList.Num(); ++i)
            {
                FString Name = SaveData->QueueList[i].ActorID;
                uint32 Pos = SaveData->QueueList[i].PositionInQueue;
                FGameStats ActsPerTurn = SaveData->QueueList[i].NumberOfActions;
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading entity: %s, %i, %i, %i"),*Name,Pos,ActsPerTurn.Remaining,ActsPerTurn.Maximum);
#endif
                UObject* NewEntity = OrderQueuePtr->AddParticipant(*Name, Pos, ActsPerTurn);
                OrderQueuePtr->AddToList(NewEntity);
            }
            return true;
        }
    }
    return false;
}

void AMatch3GameMode::SaveQueueList(USaveGame* DataPtr)
{
#if !UE_BUILD_SHIPPING
    uint32 EntitiesRecorded = 0;
#endif
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(DataPtr))
    {
        const int32 NumOfEntities = OrderQueuePtr->GetNumObjectsInList();
        
        // loop and cycle through for each element
        for(int i = 0; i < NumOfEntities; i++)
        {
            if(UObject* CurrentEntity = (OrderQueuePtr->GetFromIndex(i)))
            {
                // gather the information
                const int currentIndex = i + 1;
                FGameStats MoveStats(INIT_MAX_MOVES, INIT_MAX_MOVES);
                
                // create a new struct
                FTurnParticipantSaveData NewSaveData(CurrentEntity->GetName(),
                                                     currentIndex,
                                                     MoveStats);
                
                // add to save data
                SaveData->QueueList.Add(NewSaveData);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
                UE_LOG(LogTemp,Warning,TEXT("Saving TurnParticipant: %s, TO QUEUE POSITION: %i, REMAININGACTIONS: %i, MAXMOVES: %i"), *NewSaveData.ActorID,NewSaveData.PositionInQueue,
                       NewSaveData.NumberOfActions.Remaining, NewSaveData.NumberOfActions.Maximum);
#endif
            }
            
        }
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("OrderQueuePtr contain (%i) entities; data saved (%i) entities."), NumOfEntities, EntitiesRecorded);
        UE_LOG(LogTemp,Warning,TEXT(""));
#endif
    }
}

const bool AMatch3GameMode::TryLoadGame(const FString &SlotName, const int32 PlayerIndex)
{
    if(UGameplayStatics::DoesSaveGameExist(SlotName, PlayerIndex))
    {
        GetGameInstance<UPOdimhGameInstance>()->LoadGame(SlotName, PlayerIndex);
        return true;
    }
    
    return false;
}

void AMatch3GameMode::StartNewGame(const int32 PlayerIndex)
{
    SetNewGameState(true);
    
    if(!CreateQueueFromBlueprint())
        UE_LOG(LogTemp, Warning, TEXT("Failed to create queue list."));
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(RESET_TO_SLOT, PlayerIndex);
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
}

void AMatch3GameMode::StartTurn()
{
    GetGameState<APOdimhGameState>()->TurnNum++;
    CurrentParticipant->StartTurn();
}

void AMatch3GameMode::EndTurn()
{
    const int32 maxturn = OrderQueuePtr->GetNumObjectsInList();
    
    CurrentParticipant->EndTurn();
    
    if(GetGameState<APOdimhGameState>()->TurnNum >= maxturn)
        GameRound->End();
    
    CurrentParticipant = Cast<ATurnParticipant>(OrderQueuePtr->CycleNext());
}

void AMatch3GameMode::StartRound(const int32 ParticipantIndex)
{
    CurrentParticipant = Cast<ATurnParticipant>(OrderQueuePtr->GetFromIndex(ParticipantIndex));
    GetGameState<APOdimhGameState>()->RoundNum++;
    GameRound->Start();
}

void AMatch3GameMode::EndRound()
{
    for(int i = 0; i < OrderQueuePtr->GetNumObjectsInList(); i++)
    {
        if(ATurnParticipant* Participant = Cast<ATurnParticipant>(OrderQueuePtr->GetFromIndex(i)))
        {
            Participant->Reset();
        }
    }
    GameRound->End();
}






