// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "Gametypes.generated.h"

// constants
const uint DEFAULT_VALUE = 1; // the default number of grid moves that a game piece can make per turn
const uint DEFAULT_MOVE_COST = 1; // the default cost it takes for a grid move

/** An enum for player ID */
UENUM(BlueprintType)
enum class EPlayer : uint8
{
    One = 0,
    Two
};

// TODO: promote to a TMap?
UENUM()
enum class EMechModule : uint16
{
    Weapon = 0,
    Defense,
    Navigation,
    Max_Type
};

UENUM(BlueprintType)
enum class EDirection : uint8
{
    Up,
    Down,
    Left,
    Right,
    MaxDir
};

USTRUCT()
struct FAction
{
    GENERATED_USTRUCT_BODY()
    
public:
    FName Identifier;
    uint32 Cost;
};
