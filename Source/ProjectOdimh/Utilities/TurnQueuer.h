// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurnQueuer.generated.h"

class AGameMode;
class AMatch3GameMode;
class AQueue;

/**
 * Use to construct a queue from a list of names
 */
USTRUCT()
struct  FTurnQueuer
{
    GENERATED_BODY()
    
public:
    FTurnQueuer();
    ~FTurnQueuer();
    
    /** Create a queue list from a list of names. Will always create a "Player" entity before creating the list */
    static TArray<UObject*> CreateNewQueueList(UObject* Outer, TArray<FName> ListOfNames = TArray<FName>());
    
private:
    static UObject* CreateTurnEntity(UObject* Outer, const FName Name);
};
