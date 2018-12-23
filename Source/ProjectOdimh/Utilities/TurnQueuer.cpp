// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TurnQueuer.h"
#include "Engine/World.h"
#include "Entities/Game/Queue.h"



FTurnQueuer::FTurnQueuer()
{
    
}

FTurnQueuer::~FTurnQueuer()
{
    
}

UObject* FTurnQueuer::CreateTurnEntity(UObject* Outer, const FName Name)
{
    return NewObject<ATurnEntity>(Outer, Name);
}

TArray<UObject*> FTurnQueuer::CreateNewQueueList(UObject* Outer, TArray<FName> ListOfNames /*  = TArray<FName>() */ )
{
    TArray<UObject*> NewQueueList;
    
    NewQueueList.Add(CreateTurnEntity(Outer, "Player"));
    
    if(ListOfNames.Num() != 0)
    {
        for(FName Entity : ListOfNames)
        {
            NewQueueList.Add(CreateTurnEntity(Outer, Entity));
        }
    }
    
    return NewQueueList;
}
