// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "ProjectOdimh.h"
#include "POdimhGameState.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Queue.h"
#include "Entities/Game/TurnParticipant.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"


#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "DebuggerInfo.h"
#endif

AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    GetGameInstance<UPOdimhGameInstance>()->EventManager->InitEventHandlersList(GetWorld());
    GameRound = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(this, "Game Round", false);
    OrderQueuePtr = NewObject<AParticipantQueue>(this, "Order List");
    
    if(!TryLoadGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One))
        StartNewGame((int32)EPlayer::One);
    
    if(OrderQueuePtr->GetNumObjects() != 0)
    {
        uint32 NextParticipantIndex = 0;
        StartRound(NextParticipantIndex);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. OrderQueuePtr contain 0 objects."));
    }
}

void AMatch3GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    

}

void AMatch3GameMode::NotifySave(USaveGame* DataPtr)
{
    if(OrderQueuePtr == nullptr || OrderQueuePtr->GetNumObjects() == 0) return;
    
    SaveQueueList(DataPtr);
}

const bool AMatch3GameMode::NotifyLoad(USaveGame* Data)
{
    if(LoadQueueListFromSave(Data))
        return true;
    
    return false;
}

AGrid* AMatch3GameMode::GetGrid()
{
    return Grid;
}

void AMatch3GameMode::SetGrid(AGrid* Board)
{
    Grid = Board;
}

AParticipantQueue* AMatch3GameMode::GetOrderQueue()
{
    return OrderQueuePtr;
}

void AMatch3GameMode::AddScore(const int32 Score)
{
    GetGameState<APOdimhGameState>()->CurrentScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return GetGameState<APOdimhGameState>()->CurrentScore;
}

void AMatch3GameMode::SetCurrentScore(const int32 Score)
{
    GetGameState<APOdimhGameState>()->CurrentScore = Score;
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();
    
    
}

void AMatch3GameMode::SaveAndQuit(const int32 PlayerIndex)
{
    const bool bIgnorePlatformSpecificRestrictions = true;
    const bool bNotNewGame = false;
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex, bNotNewGame);
    
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
    AParticipantQueue* TempQueue = Cast<AParticipantQueue>(GetWorld()->SpawnActor(OrderQueueBP));
    
    UE_LOG(LogTemp,Warning,TEXT("Creating a new queue list from preassigned blueprint."));
    
    if(OrderQueuePtr)
    {
        for(int32 i = 0; i < TempQueue->GetNumObjects(); ++i)
        {
            FString Name = TempQueue->GetIndex(i)->GetName();
            uint32 Pos = i + 1;
            FGameStats ActsPerTurn = FGameStats(INIT_MAX_MOVES, INIT_MAX_MOVES);
            AController* SetController = nullptr;
            
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Creating new Participant: %s, %i, %i, %i"), *Name,Pos,ActsPerTurn.Remaining,ActsPerTurn.Maximum);
#endif
            UObject* NewEntity = OrderQueuePtr->NewParticipant(*Name, Pos, this, ActsPerTurn, SetController);
            OrderQueuePtr->AddToList(NewEntity);
        }
        
    }
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
                AController* SetController = nullptr;
                
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading entity: %s, %i, %i, %i"),*Name,Pos,ActsPerTurn.Remaining,ActsPerTurn.Maximum);
#endif
                UObject* NewEntity = OrderQueuePtr->NewParticipant(*Name, Pos, this, ActsPerTurn, SetController);
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
        const int32 NumOfEntities = OrderQueuePtr->GetNumObjects();
        
        // loop and cycle through for each element
        for(int i = 0; i < NumOfEntities; i++)
        {
            if(UObject* CurrentEntity = OrderQueuePtr->GetIndex(i))
            {
                const int currentIndex = i + 1;
                FGameStats MoveStats;
                MoveStats = FGameStats(INIT_MAX_MOVES, INIT_MAX_MOVES);
                
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
    if(!CreateQueueFromBlueprint())
        UE_LOG(LogTemp, Warning, TEXT("Failed to create queue list."));
    
    const bool bIsNewGame = true;
    GetGameState<APOdimhGameState>()->TurnCounter = 0;
    GetGameState<APOdimhGameState>()->RoundCounter = 0;
    
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(RESET_GAME_SLOT, PlayerIndex, bIsNewGame);
    GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex, bIsNewGame);
}

ATurnParticipant* AMatch3GameMode::StartRound(const int32 ParticipantIndex)
{
    if(UObject* Participant = OrderQueuePtr->GetIndex(ParticipantIndex))
    {
        GetGameState<APOdimhGameState>()->RoundCounter++;
        GameRound->ResetEvent();
        GameRound->Start();
        CurrentParticipant = Cast<ATurnParticipant>(Participant);
        UE_LOG(LogTemp, Warning, TEXT("Starting CurrentParticipant is %s."), *CurrentParticipant->GetName());
        return CurrentParticipant;
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. CurrentParticipant is nullptr."));
    
    return nullptr;
}

void AMatch3GameMode::EndRound()
{
    for(int i = 0; i < OrderQueuePtr->GetNumObjects(); i++)
    {
        if(ATurnParticipant* Participant = Cast<ATurnParticipant>(OrderQueuePtr->GetIndex(i)))
            Participant->Reset();
    }
    GameRound->End();
}

ATurnParticipant* AMatch3GameMode::GetCurrentParticipant() const
{
    return CurrentParticipant;
}




