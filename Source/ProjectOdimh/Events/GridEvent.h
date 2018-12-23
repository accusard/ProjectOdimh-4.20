// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "GridEvent.generated.h"



class AGrid;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UGridEvent : public UBaseEvent
{
	GENERATED_BODY()
	
public:
    virtual const bool IsCallerValid() override;
    
    /** When a match is detected, handle additional logic through this event function */
    UFUNCTION(BlueprintCallable)
    void HandleMatch(const int Type, const int NumTilesMatching, const int NumTilesNeeded);
    
    /** When a grid event calls for a spawning actor, handling additional logic through this event function */
    UFUNCTION(BlueprintCallable)
    void HandleSpawn(AActor* Tile);

protected:
    AGrid* Grid;
    int LastTileMatchTotal;
};

UCLASS()
class PROJECTODIMH_API UGridStateChange : public UGridEvent
{
    GENERATED_BODY()

    virtual void Process() override;
    
    /** During a grid event that calls for a state change, handle logic through this event function */
    UFUNCTION(BlueprintCallable)
    void HandleStateChange();
    
private:
    
};
