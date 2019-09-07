// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Events/BaseEvent.h"
#include "POdimhGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


UBaseEvent::UBaseEvent()
{
    bPendingFinish = true;
    bStarted = false;
}

UBaseEvent::~UBaseEvent()
{
    
}

void UBaseEvent::Init()
{
    if(!IsCallerValid()) MarkPendingKill();
    
    check(GlobalEventManager = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->EventManager);
    check(GameInstance = Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())));
}

const bool UBaseEvent::IsCallerValid()
{
    if(ensureMsgf(GetOuter(), TEXT("Expected a valid Outer to point to the event caller, but Outer is NULL.")))
        return false;
    
    UE_LOG(LogTemp, Warning, TEXT("Caller is valid but event caller does not match expected class."));
    return false;
}

void UBaseEvent::Start()
{
    bStarted = true;
    OnEventStart();
}

UObject* UBaseEvent::GetCaller()
{
    return GetOuter();
}

const bool UBaseEvent::IsPendingFinish() const
{
    return bPendingFinish;
}

const bool UBaseEvent::HasStarted() const
{
    return bStarted;
}

void UBaseEvent::End()
{

    if(bPendingFinish)
    {
        bPendingFinish = false;
        OnEventEnd();
    }
}

void UBaseEvent::Reset()
{
    bPendingFinish = true;
    bStarted = false;
}





