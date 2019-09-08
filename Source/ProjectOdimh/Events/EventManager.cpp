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
    return EventQueue->GetNumObjectsInList();
    
}

void UEventManager::InitEventQueue()
{
    if(!EventQueue)
        EventQueue = GetWorld()->SpawnActor<AQueue>();
    
}

void UEventManager::AddEvent(UBaseEvent* Event)
{
    if(EventQueue)
        EventQueue->AddToList(Event);
    else
    {
        Event->End();
        Event->MarkPendingKill();
#if !UE_BUILD_SHIPPING
        UE_LOG(LogTemp,Warning,TEXT("- Couldn't add event %s, so calling End() and kill immediately."), *Event->GetName());
#endif
    }
}

void UEventManager::EndEventsPending()
{
    for(int i = 0; i < EventQueue->GetNumObjectsInList(); ++i)
    {
        UBaseEvent* Event = Cast<UBaseEvent>(EventQueue->GetFromIndex(i));
        
        if(Event->IsPendingFinish()) Event->End();

    }
}

void UEventManager::ClearEventQueue()
{
    for(int i = 0; i < EventQueue->GetNumObjectsInList(); ++i)
    {
        EventQueue->GetFromIndex(i)->MarkPendingKill();
    }
    EventQueue->EmptyList();
}

void UEventManager::StartEventsPending()
{
    for(int i = 0; i < EventQueue->GetNumObjectsInList(); ++i)
    {
        UBaseEvent* Event = Cast<UBaseEvent>(EventQueue->GetFromIndex(i));
        
        if(!Event->HasStarted()) Event->Start();
    }
}

