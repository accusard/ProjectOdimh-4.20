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
    NewEvent->Start();
    
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

const int32 UEventManager::GetNumEventsPending() const
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
        UE_LOG(LogTemp,Warning,TEXT("Adding event: %s"), *Event->GetName());
#endif
    }
    else
    {
        Event->End();
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("- Couldn't add event %s, so calling End() immediately."), *Event->GetName());
#endif
    }
}

const int UEventManager::EndPendingEvents()
{
    int TotalEventProcessed = 0;
    
    for(int i = 1; i <= EventQueue->GetNum(); ++i)
    {
        if(UBaseEvent* Event = Cast<UBaseEvent>(EventQueue->CycleNext()))
        {
            if(Event->IsPendingFinish())
            {
                Event->End();
                TotalEventProcessed++;
            }
        }
    }
    
    EventQueue->EmptyList();
    
    return TotalEventProcessed;
}



