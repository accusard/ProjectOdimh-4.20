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

UObject* FTurnQueuer::CreateTurnParticipant(UObject* Outer, const FName Name)
{
    return NewObject<ATurnParticipant>(Outer, Name);
}

TArray<UObject*> FTurnQueuer::CreateNewQueueList(UObject* Outer, TArray<FName> ListOfNames /*  = TArray<FName>() */ )
{
    TArray<UObject*> NewQueueList;
    
    NewQueueList.Add(CreateTurnParticipant(Outer, "Player"));
    
    if(ListOfNames.Num() != 0)
    {
        for(FName Entity : ListOfNames)
        {
            NewQueueList.Add(CreateTurnParticipant(Outer, Entity));
        }
    }
    
    return NewQueueList;
}
