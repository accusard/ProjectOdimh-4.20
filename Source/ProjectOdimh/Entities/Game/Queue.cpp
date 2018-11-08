// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Queue.h"
#include "Entities/Game/TurnEntity.h"
#include "PODimhGameInstance.h"



AQueue::AQueue()
{
    Position = 0;
    PrimaryActorTick.bCanEverTick = false;
    ActiveEntity = nullptr;
}

UObject* AQueue::CycleNext()
{
    UObject* NextEntity = List[Position];
   
    if(Position >= List.Num() - 1)
        Position = 0;
    else
        Position++;
    
    ActiveEntity = NextEntity;
    return NextEntity;
}

UObject* AQueue::GetActiveEntity() const
{
    return ActiveEntity;
}

const int32 AQueue::GetNum() const
{
    return List.Num();
}

void AQueue::AddToList(UObject* ObjectToAdd)
{
    if(ActiveEntity == nullptr)
        ActiveEntity = ObjectToAdd;
    
    List.Add(ObjectToAdd);
}

void AQueue::EmptyList()
{
    ActiveEntity = nullptr;
    List.Empty();
}

void AQueue::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

