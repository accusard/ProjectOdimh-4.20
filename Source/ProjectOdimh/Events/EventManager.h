// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventManager.generated.h"

class UBaseEvent;
class UEventListener;
class UGridEvent;
class AQueue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGlobalWidgetDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGridStateChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateFromComponentDelegate, AActor*, Spawner, UActorComponent*, Comp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTileMatch, const int, TileType, const int, NumTilesMatching, const int, NumTilesNeeded);

/**
 * Contains delegates used for multicasting
 */
UCLASS()
class PROJECTODIMH_API UEventManager : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventManager();
    
    /** Create a game event. */
    UFUNCTION(BlueprintCallable)
    UBaseEvent* Create(UBaseEvent* NewEvent);
    
    /** Iterate through actors in the active UWorld and place in Event Handler list. */
    UFUNCTION(BlueprintCallable)
    void InitEventHandlersList(UWorld* World);
    
    void InitEventQueue();
    void AddEvent(UBaseEvent* Event);
    void FinishProcessEvents();
    const int32 GetNumElementInQueue() const;
    
    // delegates
    UPROPERTY(BlueprintAssignable)
    FTileMatch OnTileMatch;
    UPROPERTY(BlueprintAssignable)
    FGridStateChange OnGridStateChange;
    UPROPERTY(BlueprintAssignable)
    FCreateFromComponentDelegate OnSpawnFromComponent;
    UPROPERTY(BlueprintAssignable)
    FGlobalWidgetDelegate OnInteractWidget;
    
private:
    /** The list of active event handlers */
    UPROPERTY()
    TArray<UActorComponent*> EventHandlers;
    
    UPROPERTY()
    AQueue* EventQueue;
};
