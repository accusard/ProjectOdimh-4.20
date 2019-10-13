// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "Match3GameMode.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Entities/Game/ParticipantTurn.h"
#include "Entities/Game/Grid.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"
#include "Events/EventManager.h"



AMatch3GameMode::AMatch3GameMode()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AMatch3GameMode::StartPlay()
{
    Super::StartPlay();
    
    // initialize
    bool bIsNewGame = false;
    const bool bStartRoundNow = false;
    const int32 Player1 = (int32)EPlayer::One;
    
    GetGameInstance<UPOdimhGameInstance>()->EventManager->InitEventHandlersList(GetWorld());
    GameRound = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(this, "Game Round", bStartRoundNow);
    
    if(!TryLoadGame(CONTINUE_GAME_SLOT, Player1))
        bIsNewGame = StartNewGame();
    
    if(Participants.Num() != 0)
    {
        const uint32 NextParticipant = GetGameState<APOdimhGameState>()->NextParticipantIndex;

        StartRound(NextParticipant);
        if(bIsNewGame)
        {
            GetGameInstance<UPOdimhGameInstance>()->SaveGame(RESET_GAME_SLOT, Player1, bIsNewGame);
            GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, Player1, bIsNewGame);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. Participants contain 0 objects."));
    }
}

void AMatch3GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    

}

void AMatch3GameMode::NotifySave(USaveGame* DataPtr)
{
    // save current score
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
        Data->Board.GameScore = GetCurrentScore();
    
    if(Participants.Num() == 0) return;
    
    SaveParticipants(DataPtr);
}

const bool AMatch3GameMode::NotifyLoad(USaveGame* DataPtr)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(DataPtr))
        SetCurrentScore(Data->Board.GameScore);
    
    return LoadParticipants(DataPtr);
}

TMap<uint32, AParticipantTurn*>& AMatch3GameMode::GetParticipants()
{
    return Participants;
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

const bool AMatch3GameMode::ParticipantsBlueprintIsValid()
{
    if(ParticipantsBlueprint.Num() == 0)
    {
        UE_LOG(LogTemp,Warning,TEXT("ParticipantsBlueprint contain no element."));
        return false;
    }
    
    for(auto& Check : ParticipantsBlueprint)
    {
        AParticipantTurn* IsValid = Check.Value.GetDefaultObject();
        uint32 TurnOrder = Check.Key;
        
        if(IsValid && TurnOrder > 0)
            continue;
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("ParticipantsBlueprint contain invalid data. Ensure blueprint is assigned in GameMode and TurnOrder is greater than 0."));
            return false;
        }
    }
    
    return true;
}

const bool AMatch3GameMode::LoadParticipantsFromBlueprint()
{
    UE_LOG(LogTemp,Warning,TEXT("Creating a Participants list from preassigned blueprint."));

    for(auto& Elem : ParticipantsBlueprint)
    {
        if(AParticipantTurn* Participant = NewParticipant(Elem.Value, this))
        {
            FString Name = Participant->GetName();
            const FGameStats& ActsPerTurn = Participant->GetActionComponent()->ActionCount;
            AController* SetController = Participant->GetGridController();
            
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT("Creating new Participant: %s, %i, %i, %i"), *Name, Elem.Key, ActsPerTurn.Remaining, ActsPerTurn.Maximum);
#endif
            Participants.Add(Elem.Key, Participant);
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("Failed to load Participants from blueprint."))
            return false;
        }
    }
        
    return true;
}

const bool AMatch3GameMode::LoadParticipants(USaveGame* Data)
{
    // load from save
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(Data))
    {
        GetGameState<APOdimhGameState>()->NextParticipantIndex = SaveData->CurrentParticipantIndex;
        if(SaveData->ParticipantsRegistry.Num() != 0)
        {
            for(int32 i = 0; i < SaveData->ParticipantsRegistry.Num(); ++i)
            {
                const FString& Name = SaveData->ParticipantsRegistry[i].Name;
                uint32 TurnNum = SaveData->ParticipantsRegistry[i].PositionInQueue;
                FGameStats ActsPerTurn = SaveData->ParticipantsRegistry[i].NumberOfActions;
                AController* SetController = nullptr;
                
#if !UE_BUILD_SHIPPING
                UE_LOG(LogTemp,Warning,TEXT("Loading Participant: %s, %i, %i, %i"),*Name, TurnNum, ActsPerTurn.Remaining, ActsPerTurn.Maximum);
#endif
                AParticipantTurn* NewEntity = NewParticipant(*Name, this, ActsPerTurn, SetController);
                Participants.Add(TurnNum, NewEntity);
            }
            return true;
        }
    }
    return false;
}

void AMatch3GameMode::SaveParticipants(USaveGame* DataPtr)
{
#if !UE_BUILD_SHIPPING
    uint32 EntitiesRecorded = 0;
#endif
    if(UPOdimhSaveGame* SaveData = Cast<UPOdimhSaveGame>(DataPtr))
    {
        const int32 NumOfEntities = Participants.Num();
        SaveData->CurrentParticipantIndex = GetGameState<APOdimhGameState>()->NextParticipantIndex;
        
        // loop and cycle through for each element
//        for(int i = 0; i < Participants.Num(); i++)
        for(auto& Elem : Participants)
        {
            if(AParticipantTurn* CurrentEntity = Elem.Value)
            {
                const FGameStats& MoveStats = CurrentEntity->GetActionComponent()->ActionCount;
                
                FParticipantInfo NewInfo(CurrentEntity->GetName(),
                                                     Elem.Key,
                                                     MoveStats);
                
                // add to save data
                SaveData->ParticipantsRegistry.Add(NewInfo);
#if !UE_BUILD_SHIPPING
                EntitiesRecorded++;
                UE_LOG(LogTemp,Warning,TEXT("Saving Participant: %s, QUEUE POSITION: %i, ACTIONSREMAINING: %i, ACTIONSMAX: %i"), *NewInfo.Name, NewInfo.PositionInQueue,
                       NewInfo.NumberOfActions.Remaining, NewInfo.NumberOfActions.Maximum);
#endif
            }
            
        }
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("Participants contain (%i) entities; data saved (%i) entities."), NumOfEntities, EntitiesRecorded);
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

const bool AMatch3GameMode::StartNewGame()
{
    if(ParticipantsBlueprintIsValid() && LoadParticipantsFromBlueprint())
    {
        GetGameState<APOdimhGameState>()->TurnCounter = 0;
        GetGameState<APOdimhGameState>()->RoundCounter = 0;
        GetGameState<APOdimhGameState>()->NextParticipantIndex = 1;
        return true;
    }
    return false;
}

AParticipantTurn* AMatch3GameMode::StartRound(const uint32 ParticipantTurnNum)
{
    CurrentParticipant = nullptr;
    
    if(AParticipantTurn* NextParticipant = Participants[ParticipantTurnNum])
    {
        GetGameState<APOdimhGameState>()->RoundCounter++;
        GameRound->ResetEvent();
        GameRound->Start();
        CurrentParticipant = NextParticipant;
        OnRoundStart(ParticipantTurnNum);
        
        UE_LOG(LogTemp, Warning, TEXT("Starting CurrentParticipant is %s."), *CurrentParticipant->GetName());
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. CurrentParticipant is nullptr."));
    
    return CurrentParticipant;
}

void AMatch3GameMode::EndRound()
{
    for(int i = 0; i < Participants.Num(); i++)
    {
        if(AParticipantTurn* Participant = Cast<AParticipantTurn>(Participants[i]))
            Participant->Reset();
    }
    GameRound->End();
    
    OnRoundEnd();
}

void AMatch3GameMode::ReceiveRequestToEndTurn(AParticipantTurn* Participant)
{
    OnReceivedEndTurn(Participant);
    Participant->EndTurn();
}

void AMatch3GameMode::ReceiveRequestToEndTurn(AParticipantTurn* Participant, ATile* LastTileGrabbed)
{
    if(Grid->HasTilePositionChanged(LastTileGrabbed))
        ReceiveRequestToEndTurn(Participant);
}

AParticipantTurn* AMatch3GameMode::GetCurrentParticipant() const
{
    return CurrentParticipant;
}

AParticipantTurn* AMatch3GameMode::NewParticipant(const FName Name, AGameModeBase* GameMode, const FGameStats &NumberOfActions, AController* GridController)
{
    FActorSpawnParameters Params;
    Params.Name = Name;
    Params.Owner = GameMode;
    
    AParticipantTurn* NewEntity = GetWorld()->SpawnActor<AParticipantTurn>(AParticipantTurn::StaticClass(), Params);
    NewEntity->Init(GameMode, NumberOfActions, GridController);
    
    return NewEntity;
}

AParticipantTurn* AMatch3GameMode::NewParticipant(TSubclassOf<AParticipantTurn> Blueprint, AGameModeBase* GameMode)
{
    AParticipantTurn* NewEntity = GetWorld()->SpawnActor<AParticipantTurn>(Blueprint);

    const FGameStats& NumOfActions = NewEntity->GetActionComponent()->ActionCount;
    AController* GridController = NewEntity->GetGridController();
    
    NewEntity->Init(GameMode, NumOfActions, GridController);
    
    return NewEntity;
}

void AMatch3GameMode::HandleTilesSwapped(ATile* DynamicTile, ATile* StaticTile)
{
    HandleCurrentParticipantSwappedTiles();
}

void AMatch3GameMode::HandleCurrentParticipantSwappedTiles()
{
    FMatch3GameAction Action;
    Action.Identifier = TILES_SWAPPED_POSITIONS;
    Action.Cost = DEFAULT_MOVE_COST;
    Action.GameMode = this;
    
    Give(CurrentParticipant, Action);
}

void AMatch3GameMode::Give(AParticipantTurn* Participant, const FMatch3GameAction& Action, const bool bExecuteNow)
{
    if(Participant->GetActionComponent() && bExecuteNow)
        Participant->Execute(Action);
}

AGrid* AMatch3GameMode::GetGrid() const
{
    return Grid;
}

