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
struct FMechData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FVector Position;
};

/**
 * The struct that contain the save data of the combat board
 */
USTRUCT()
struct FBoardstateData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FBoardstateData()
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
struct FTurnEntityData
{
    GENERATED_USTRUCT_BODY()
    
public:
    FTurnEntityData();
    FTurnEntityData(const FString &Name, const uint32 TurnPosition, const FGameStats &RemainingMoves, const bool bHasFinished);
    
    FString ActorID;
    uint32 PositionInQueue;
    FGameStats NumberOfMoves;
    bool bFinishMoves;
    
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
    FBoardstateData Board;
    
    /** The list of mechs contained in a given game */
    UPROPERTY()
    TArray<FMechData> MechList;
    
    /** Data for the turn queue */
    UPROPERTY()
    TArray<FTurnEntityData> QueueList;
};
