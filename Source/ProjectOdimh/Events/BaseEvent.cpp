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

void UBaseEvent::End()
{

    if(bPendingFinish)
    {
        bPendingFinish = false;
        OnEventEnd();
        MarkPendingKill();
    }
}






