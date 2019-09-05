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

UObject* ATurnBasedQueue::AddParticipant(const FName Name)
{
    return NewObject<ATurnParticipant>(this, Name);
}

UObject* ATurnBasedQueue::AddParticipant(const FName Name, const uint32 TurnOrder, const FGameStats &NumberOfMoves)
{
    ATurnParticipant* NewEntity = Cast<ATurnParticipant>(AddParticipant(Name));
    NewEntity->SetTurnOrder(TurnOrder);
    NewEntity->InitMovement(NumberOfMoves);
    
    return NewEntity;
}

void ATurnBasedQueue::CreateFromNames(TArray<FName> ListOfNames /*  = TArray<FName>() */ )
{
    TArray<UObject*> NewQueueList;
    
    if(ListOfNames.Num() != 0)
    {
        for(FName Entity : ListOfNames)
        {
            NewQueueList.Add(AddParticipant(Entity));
        }
    }
    
    CreateFromObjects(NewQueueList);
}

void ATurnBasedQueue::CreateFromObjects(TArray<UObject*> QueList)
{
    for(UObject* Entity : QueList)
    {
        AddToList(Entity);
    }
}

void ATurnBasedQueue::SortTurnOrder()
{
    TArray<SortNumData> SortingArray;
    TArray<UObject*> Result;
    
    for(auto* Entity : List)
    {
        if(ATurnParticipant* TurnParticipant = Cast<ATurnParticipant>(Entity))
        {
            SortNumData SortingData(TurnParticipant, TurnParticipant->GetTurnOrder());
            SortingArray.Add(SortingData);
        }
    }
    
    MySortingClass Sort;
    Sort.MergeSort(SortingArray);
    
    for(auto SortedData : SortingArray)
    {
        Result.Add(SortedData.ObjPtr);
    }
    
    List = Result;
}
