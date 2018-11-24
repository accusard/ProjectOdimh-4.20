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

FTurnEntitySaveData::FTurnEntitySaveData()
{
    ActorID = FString("Empty");
    PositionInQueue = 0;
    NumberOfMoves = FGameStats();
\
}

FTurnEntitySaveData::FTurnEntitySaveData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingMoves)
{
    ActorID = Name;
    PositionInQueue = TurnPosition;
    NumberOfMoves = RemainingMoves;
   
}

UPOdimhSaveGame::UPOdimhSaveGame()
{
    SaveSlotName = DEFAULT_SAVE_SLOT;
    UserIndex = 0;
}




