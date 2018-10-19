// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PendingKillQueue.h"
#include "Events/BaseEvent.h"
#include "POdimhGameInstance.h"



APendingKillQueue::APendingKillQueue()
{
    PrimaryActorTick.bCanEverTick = true;
    SetActorTickInterval(INIT_KILL_INTERVALS);
}

void APendingKillQueue::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    KillList();
}

void APendingKillQueue::KillList()
{
    for(UObject* Object : List)
    {
        if(Object->IsValidLowLevel() && !Object->IsPendingKill())
            Object->MarkPendingKill();
    }
    List.Empty();
}

void APendingKillQueue::SetKillInterval(float Seconds)
{
    SetActorTickInterval(Seconds);
}
