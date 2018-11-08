// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhSaveGame.h"


UPOdimhSaveGame::UPOdimhSaveGame()
{
    SaveSlotName = DEFAULT_SAVE_SLOT;
    UserIndex = 0;
    GameScore = 0;
}

FTurnQueueData::FTurnQueueData()
{
    ActorID = FString("Empty");
    PositionInQueue = 0;
    NumberOfMoves = FGameStats();
    bFinishMoves = false;
}

FTurnQueueData::FTurnQueueData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingMoves, const bool bHasFinished)
{
    ActorID = Name;
    PositionInQueue = TurnPosition;
    NumberOfMoves = RemainingMoves;
    bFinishMoves = bHasFinished;
}
