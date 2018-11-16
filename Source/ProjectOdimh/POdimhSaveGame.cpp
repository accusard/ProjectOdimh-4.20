// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhSaveGame.h"


UPOdimhSaveGame::UPOdimhSaveGame()
{
    SaveSlotName = DEFAULT_SAVE_SLOT;
    UserIndex = 0;
}

void FBoardstateData::AddTile(int Type)
{
    TileTypes.Add(Type);
}

const int32 FBoardstateData::GetNumberOfTiles() const
{
    return TileTypes.Num();
}

FTurnEntityData::FTurnEntityData()
{
    ActorID = FString("Empty");
    PositionInQueue = 0;
    NumberOfMoves = FGameStats();
    bFinishMoves = false;
}

FTurnEntityData::FTurnEntityData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingMoves, const bool bHasFinished)
{
    ActorID = Name;
    PositionInQueue = TurnPosition;
    NumberOfMoves = RemainingMoves;
    bFinishMoves = bHasFinished;
}
