// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "EventManager.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Events/GridEvent.h"
#include "Events/GameEvent.h"
#include "Components/EventListener.h"
#include "Entities/Game/Queue.h"


// Sets default values for this component's properties
UEventManager::UEventManager()
{
    EventQueue = CreateDefaultSubobject<AQueue>("Event Queue");
    InitEventQueue();
}

UBaseEvent* UEventManager::Create(UBaseEvent* NewEvent)
{
    NewEvent->InitializeEvent();
    AddEvent(NewEvent);
    NotifyEventHandlers(NewEvent);
    NewEvent->Process();
    
    return NewEvent;
}

void UEventManager::InitEventHandlersList(UWorld* World)
{
    
    UActorComponent* ListenerComponentPtr;
    for(TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        ListenerComponentPtr = ActorItr->FindComponentByClass<UEventListener>();
        if(ListenerComponentPtr)
        {
            EventHandlers.Add(ListenerComponentPtr);
        }
        
        ListenerComponentPtr = nullptr;
    }
    
}

void UEventManager::NotifyEventHandlers(UBaseEvent* Event)
{
    for(auto Ptr : EventHandlers)
    {
        if( UEventListener* Handler = Cast<UEventListener>(Ptr))
        {
            Handler->RegisterEvent(Event);
        }
            
    }

}

const int32 UEventManager::GetNumElementInQueue() const
{
    return EventQueue->GetNum();
    
}

void UEventManager::InitEventQueue()
{
    if(!EventQueue)
        EventQueue = GetWorld()->SpawnActor<AQueue>();
    
}

void UEventManager::AddEvent(UBaseEvent* Event)
{
    if(EventQueue)
    {
        EventQueue->AddToList(Event);
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("... adding event: %s"), *Event->GetName());
#endif
    }
    else
    {
        Event->Finish();
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("- Couldn't add event %s, so calling Finish() immediately."), *Event->GetName());
#endif
    }
}

void UEventManager::FinishProcessEvents()
{
#if !UE_BUILD_SHIPPING
    int EventNum = 0;
    UE_LOG(LogTemp,Warning,TEXT(" number of elements in queue: %i"), EventQueue->GetNum());
#endif
    for(int i = 1; i <= EventQueue->GetNum(); ++i)
    {
        if(UBaseEvent* Event = Cast<UBaseEvent>(EventQueue->CycleNext()))
        {
#if !UE_BUILD_SHIPPING
            UE_LOG(LogTemp,Warning,TEXT(" finishing: %s"), *Event->GetName());
#endif
            Event->Finish();
            EventNum++;
        }
    }
    
    EventQueue->EmptyList();
#if !UE_BUILD_SHIPPING
    UE_LOG(LogTemp,Warning,TEXT(" elements in queue processed: %i"), EventNum);
    UE_LOG(LogTemp,Warning,TEXT("***"));
#endif
}



