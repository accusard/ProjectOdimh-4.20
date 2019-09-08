// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Events/BaseEvent.h"
#include "EventManager.generated.h"

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
    
    template<class T>
    T* NewEvent(UObject* Outer, FName Name, const bool bStartNow)
    {
        T* NewEvent = NewObject<T>(Outer, Name);
        if(UBaseEvent* Event = Cast<UBaseEvent>(NewEvent))
        {
            Event->Init();
            if(bStartNow) Event->Start();
            
            AddEvent(Event);
            
            return static_cast<T*>(NewEvent);
        }
        else
        {
            Cast<UObject>(NewEvent)->MarkPendingKill();
            return nullptr;
        }
    }
    
    /** Iterate through actors in the active UWorld and place in Event Handler list. */
    void InitEventHandlersList(UWorld* World);
    
    void InitEventQueue();
    
    void AddEvent(UBaseEvent* Event);
    
    void EndEventsPending();
    
    void StartEventsPending();
    
    void ClearEventQueue();
    
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
