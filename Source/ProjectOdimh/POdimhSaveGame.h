// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Entities/Game/Tile.h"
#include "POdimhSaveGame.generated.h"

const FString DEFAULT_SAVE_SLOT = "DefaultSlotName";
const FString RESET_TO_SLOT = "ResetLevel";
const FString CONTINUE_GAME_SLOT = "ContinueGame";

/**
 * The struct that contain the save data of the mech
 */
USTRUCT()
struct FMechSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FVector Position;
};

/**
 * The struct that contain the save data of the combat board
 */
USTRUCT()
struct FBoardSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FBoardSaveData()
    {
        GameScore = 0;
    }
    /** Add to the data the type of tile */
    void AddTile(int Type);
    
    /** Get the total tiles that data contained */
    const int32 GetNumberOfTiles() const;
    
    /** Data to hold tile types */
    UPROPERTY()
    TArray<int> TileTypes;
    
    /** The data for game score */
    UPROPERTY()
    int32 GameScore;
};

USTRUCT()
struct FTurnEntitySaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FTurnEntitySaveData();
    FTurnEntitySaveData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingMoves);
    
    UPROPERTY()
    FString ActorID;
    UPROPERTY()
    uint32 PositionInQueue;
    UPROPERTY()
    FGameStats NumberOfMoves;

    
};

/**
 * An object that contains the save data of the game
 */
UCLASS()
class PROJECTODIMH_API UPOdimhSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    // default constructor
    UPOdimhSaveGame();
    
    /** The name of the save slot */
    UPROPERTY()
    FString SaveSlotName;
    
    /** The user who is doing the save */
    UPROPERTY()
    uint32 UserIndex;
    
    /** The state of the board as well as the current score is kept here */
    UPROPERTY()
    FBoardSaveData Board;
    
    /** The list of mechs contained in a given game */
    UPROPERTY()
    TArray<FMechSaveData> MechList;
    
    /** Data for the turn queue */
    UPROPERTY()
    TArray<FTurnEntitySaveData> QueueList;
};
