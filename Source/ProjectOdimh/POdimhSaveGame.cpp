// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhSaveGame.h"



FMechSaveData::FMechSaveData()
{
    bReset = 0;
}

void FBoardSaveData::AddTile(int Type)
{
    TileTypes.Add(Type);
}

const int32 FBoardSaveData::GetNumberOfTiles() const
{
    return TileTypes.Num();
}

FTurnParticipantSaveData::FTurnParticipantSaveData()
{
    ActorID = FString("Empty");
    PositionInQueue = 0;
    NumberOfActions = FGameStats();
\
}

FTurnParticipantSaveData::FTurnParticipantSaveData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingActions)
{
    ActorID = Name;
    PositionInQueue = TurnPosition;
    NumberOfActions = RemainingActions;
   
}

UPOdimhSaveGame::UPOdimhSaveGame()
{
    SaveSlotName = DEFAULT_SAVE_SLOT;
    UserIndex = 0;
    
    DEFAULT = DEFAULT_SAVE_SLOT;
    RESET = RESET_GAME_SLOT;
    CONTINUE = CONTINUE_GAME_SLOT;
}




