// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "Queue.h"
#include "Entities/Game/TurnParticipant.h"
#include "PODimhGameInstance.h"



AQueue::AQueue()
{
    Index = 0;
    PrimaryActorTick.bCanEverTick = false;
}

UObject* AQueue::CycleNext()
{
    Index++;
    
    if(Index > List.Num() - 1)
        Index = 0;
    
    return List[Index];
}

void AQueue::BeginPlay()
{
    Super::BeginPlay();
}

const int32 AQueue::GetNumObjectsInList() const
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

UObject* AQueue::GetFromIndex(const int32 index) const
{
    return List[index];
}

void AQueue::SetCurrentIndex(const int32 index)
{
    Index = FMath::Clamp<int32>(index, 0, List.Num());
}

const int32 AQueue::GetCurrentIndex() const
{
    return Index;
}

UObject* ATurnBasedQueue::NewParticipant(const FName Name)
{
    return NewObject<ATurnParticipant>(this, Name);
}

UObject* ATurnBasedQueue::NewParticipant(const FName Name, const uint32 QueuePos, AGameModeBase* GameMode, const FGameStats &NumberOfActions)
{
    ATurnParticipant* NewEntity = Cast<ATurnParticipant>(NewParticipant(Name));
    NewEntity->Init(QueuePos, GameMode, NumberOfActions);
    
    return NewEntity;
}
