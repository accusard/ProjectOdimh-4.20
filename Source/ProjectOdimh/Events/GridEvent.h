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
    UFUNCTION(BlueprintCallable)
    void BroadcastTileMatch(const int TileType, const int TilesNum, const int MatchNum);
    UFUNCTION(BlueprintCallable)
    void BroadcastStateChange();
    UFUNCTION(BlueprintCallable)
    void BroadcastComponentSpawn(AActor* SpawnedActor, UActorComponent* Instigator);
    
      
    
private:

};

UCLASS()
class PROJECTODIMH_API UGridStateChange : public UGridEvent
{
    GENERATED_BODY()
    
    
    virtual const bool IsCallerValid() override;
    virtual void Process() override;
    
private:
    AGrid* Grid;
};
