// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Queue.h"
#include "Entities/Game/TurnEntity.h"
#include "PODimhGameInstance.h"



AQueue::AQueue()
{
    Position = 0;
    PrimaryActorTick.bCanEverTick = true;
}

UObject* AQueue::CycleNext()
{
    UObject* NextEntity = List[Position];
    Position++;
    
    if(Position >= List.Num())
        Position = 0;
    
    return NextEntity;
}

const int32 AQueue::GetNum() const
{
    return List.Num();
}

void AQueue::AddToList(UObject* ObjectToAdd)
{
    List.Add(ObjectToAdd);
}

void AQueue::EmptyList()
{
    List.Empty();
}

void AQueue::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

