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
    PGameState = GetGameState<APOdimhGameState>();
    
    GetGameInstance<UPOdimhGameInstance>()->EventManager->InitEventHandlersList(GetWorld());
    GameRound = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(this, "Game Round", bStartRoundNow);
    
    if(!TryLoadGame(CONTINUE_GAME_SLOT, Player1))
        bIsNewGame = StartNewGame();
    
    if(Participants.Num() != 0)
    {
        const uint32 NextParticipant = PGameState->ParticipantIndex;

        StartRound(NextParticipant);
        if(bIsNewGame)
        {
            GetGameInstance<UPOdimhGameInstance>()->SaveGame(RESET_GAME_SLOT, Player1, bIsNewGame);
            GetGameInstance<UPOdimhGameInstance>()->SaveGame(CONTINUE_GAME_SLOT, Player1, bIsNewGame);
        }
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Error starting round. Participants contain 0 objects."));
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
    PGameState->CurrentScore += Score;
}

const int AMatch3GameMode::GetCurrentScore()
{
    return PGameState->CurrentScore;
}

void AMatch3GameMode::SetCurrentScore(const int32 Score)
{
    PGameState->CurrentScore = Score;
}

void AMatch3GameMode::BeginPlay()
{
    Super::BeginPlay();
    
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorReleased.AddUniqueDynamic(this, &AMatch3GameMode::ReceiveActorReleasedNotification);
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
            FString Name = Participant->GetDisplayName();
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
        PGameState->ParticipantIndex = SaveData->CurrentParticipantIndex;
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
        SaveData->CurrentParticipantIndex = PGameState->ParticipantIndex;
        
        // loop and cycle through for each element
//        for(int i = 0; i < Participants.Num(); i++)
        for(auto& Elem : Participants)
        {
            if(AParticipantTurn* CurrentEntity = Elem.Value)
            {
                const FGameStats& MoveStats = CurrentEntity->GetActionComponent()->ActionCount;
                
                FParticipantInfo NewInfo(CurrentEntity->GetDisplayName(),
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
        PGameState->TurnCounter = 0;
        PGameState->RoundCounter = 0;
        PGameState->ParticipantIndex = 1;
        return true;
    }
    return false;
}

AParticipantTurn* AMatch3GameMode::StartRound(const uint32 ParticipantTurnNum)
{
    CurrentParticipant = nullptr;
    
    if(AParticipantTurn* NextParticipant = Participants[ParticipantTurnNum])
    {
        PGameState->RoundCounter++;
        GameRound->ResetEvent();
        GameRound->Start();
        CurrentParticipant = NextParticipant;
        StartTurn(ParticipantTurnNum, nullptr);
        OnRoundStart();
    }
    
    return CurrentParticipant;
}

void AMatch3GameMode::EndRound()
{
    for(int i = 1; i <= Participants.Num(); i++)
    {
        if(AParticipantTurn* Participant = Cast<AParticipantTurn>(Participants[i]))
            Participant->Reset();
    }
    ActiveTurn->End();
    GameRound->End();
    OnRoundEnd();
    PGameState->ParticipantIndex = 1;
    StartTurn(PGameState->ParticipantIndex, nullptr);
}

void AMatch3GameMode::ReceiveRequestToEndTurn()
{
    if(Grid->IsTilesBursting() || IsTurnPending())
        return;
    
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        OnReceivedEndTurn(ActiveParticipant);
        
        // next turn
        for(uint32 i = ++PGameState->ParticipantIndex; i <= Participants.Num(); ++i)
        {
            if(StartTurn(i, nullptr))
                return;
            else
                continue;
        }
        
        // end of round
        EndRound();
    }
}

void AMatch3GameMode::ReceiveRequestToEndTurn(ATile* LastTileGrabbed)
{
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        if(Grid->HasTilePositionChanged(LastTileGrabbed))
            ReceiveRequestToEndTurn();
        else
            ActiveParticipant->GetActionComponent()->RestoreActionMax();
    }
}

AParticipantTurn* AMatch3GameMode::GetCurrentParticipant() const
{
    return Cast<AParticipantTurn>(ActiveTurn->GetOwner());
}

AParticipantTurn* AMatch3GameMode::NewParticipant(const FName Name, AGameModeBase* GameMode, const FGameStats &NumberOfActions, AController* GridController)
{
    FActorSpawnParameters Params;
    Params.Name = Name;
    Params.Owner = GameMode;
    
    AParticipantTurn* NewEntity = GetWorld()->SpawnActor<AParticipantTurn>(AParticipantTurn::StaticClass(), Params);
    NewEntity->Init(*Name.ToString(), GameMode, NumberOfActions, GridController);
    
    return NewEntity;
}

AParticipantTurn* AMatch3GameMode::NewParticipant(TSubclassOf<AParticipantTurn> Blueprint, AGameModeBase* GameMode)
{
    AParticipantTurn* NewEntity = GetWorld()->SpawnActor<AParticipantTurn>(Blueprint);

    const FGameStats& NumOfActions = NewEntity->GetActionComponent()->ActionCount;
    AController* GridController = NewEntity->GetGridController();
    
    NewEntity->Init(*NewEntity->GetDisplayName(), GameMode, NumOfActions, GridController);
    
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
    // give to the current active participant
    if(bExecuteNow &&  Participant == GetCurrentParticipant() && Participant->GetActionComponent())
        Participant->Execute(Action, ActiveTurn);
    
    // TODO: give to pending action?
}

AGrid* AMatch3GameMode::GetGrid() const
{
    return Grid;
}

void AMatch3GameMode::StartTurn(AParticipantTurn* Participant, APawn* InPawn)
{
    if(Participant)
    {
        if(ActiveTurn && !ActiveTurn->IsPendingKill())
        {
            ActiveTurn->End();
            ActiveTurn->MarkPendingKill();
        }
        const bool bStartTurnNow = true;
        FString TurnDescription = Participant->GetDisplayName();
        TurnDescription.Append("'s Turn");
        
        ActiveTurn = GetGameInstance<UPOdimhGameInstance>()->EventManager->NewEvent<UGameEvent>(Participant, FName(*TurnDescription), bStartTurnNow);
        
        if(InPawn)
            Participant->GetGridController()->Possess(InPawn);
        else
            UE_LOG(LogTemp, Warning, TEXT("TODO: Need GridController and InPawn to possess."));
        
        UE_LOG(LogTemp, Warning, TEXT("DebugTurn: Starting Turn: %s."), *Participant->GetDisplayName());
        
        PGameState->TurnCounter++;
        OnTurnStart(*Participant->GetDisplayName());
    }
}

const bool AMatch3GameMode::StartTurn(const uint32 Index, APawn* InPawn)
{
    if(Participants.Contains(Index))
    {
        PGameState->ParticipantIndex = Index;
        StartTurn(Participants[Index], InPawn);
        return true;
    }
    return false;
}

void AMatch3GameMode::ReceiveActorReleasedNotification(AActor* ReleasedActor)
{
    if(ActiveTurn)
    {
        if(ATile* Tile = Cast<ATile>(ReleasedActor))
            ReceiveRequestToEndTurn(Tile);
    }
}

void AMatch3GameMode::EndTurn()
{
    ActiveTurn->End();
    if(AParticipantTurn* ActiveParticipant = GetCurrentParticipant())
    {
        if(AController* GridController = ActiveParticipant->GetGridController())
            GridController->UnPossess();
    }
}

const bool AMatch3GameMode::IsTurnPending() const
{
    if(ActiveTurn)
        return ActiveTurn->IsPendingFinish();
    else
        return false;
}
