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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateFromComponentDelegate, AActor*, Spawner, UActorComponent*, Comp);

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
    
    template<class T*>
    T* CreateEvent(UObject* Outer, FName Name, const bool bStartNow);
    
    /** Iterate through actors in the active UWorld and place in Event Handler list. */
    UFUNCTION(BlueprintCallable)
    void InitEventHandlersList(UWorld* World);
    
    void InitEventQueue();
    
    void AddEvent(UBaseEvent* Event);
    
    UFUNCTION(BlueprintCallable)
    const int EndPendingEvents();
    
    const int32 GetNumEventsPending() const;
    
    UPROPERTY(BlueprintAssignable)
    FCreateFromComponentDelegate OnSpawnFromComponent;
    
    UPROPERTY(BlueprintAssignable)
    FGlobalWidgetDelegate OnInteractWidget;
    
private:
    /** The list of active event handlers */
    UPROPERTY()
    TArray<UActorComponent*> EventHandlers;
    
    /** A list of events that are pending processing */
    UPROPERTY()
    AQueue* EventQueue;
};
