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
 * The struct that contain the save data of the grid 
 */
USTRUCT()
struct FGridSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    /** TODO: may not need structs */
};

/**
 * The struct that contain the save data of the combat board
 */
USTRUCT()
struct FCombatBoardSaveData
{
    GENERATED_USTRUCT_BODY()
    
public:
    /** TODO: may not need struct */
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
    
    /** Data to hold tile types */
    UPROPERTY()
    TArray<int> TileTypes;
    
    /** The data for game score */
    UPROPERTY()
    int32 GameScore;
};
