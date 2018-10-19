// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Events/BaseEvent.h"
#include "POdimhGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


UBaseEvent::UBaseEvent()
{
    bPendingFinish = true;
}

UBaseEvent::~UBaseEvent()
{
    
}

void UBaseEvent::InitializeEvent()
{
    if(!IsCallerValid()) MarkPendingKill();
    
    check(GlobalEventManager = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GlobalEvent);
}

const bool UBaseEvent::IsCallerValid()
{
    if(ensureMsgf(GetOuter(), TEXT("Expected a valid Outer to point to the event caller.")))
    {
        return false;
    }
    
    return true;
}

UObject* UBaseEvent::GetCaller()
{
    return GetOuter();
}

const bool UBaseEvent::IsPendingFinish() const
{
    return bPendingFinish;
}

void UBaseEvent::Finish()
{
    if(bPendingFinish)
    {
        bPendingFinish = false;
        MarkPendingKill();
    }
}






