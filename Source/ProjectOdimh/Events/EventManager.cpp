// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "EventManager.h"
#include "Events/GridEvent.h"
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
    NewEvent->Process();
    AddEvent(NewEvent);
    NotifyEventHandlers(NewEvent);
    
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
        UE_LOG(LogTemp,Warning,TEXT("Adding to event queue: %s"), *Event->GetName());
#endif
    }
    else
        Event->Finish();
    
}

void UEventManager::FinishProcessEvents()
{
    for(int i = 1; i <= EventQueue->GetNum(); ++i)
    {
        if(UBaseEvent* Event = Cast<UBaseEvent>(EventQueue->CycleNext())) Event->Finish();
    }
    
    EventQueue->EmptyList();
}



