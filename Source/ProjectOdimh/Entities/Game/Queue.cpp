// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Queue.h"
#include "Entities/Game/TurnEntity.h"
#include "PODimhGameInstance.h"



AQueue::AQueue()
{
    CurrentIndex = 0;
    PrimaryActorTick.bCanEverTick = false;
    ActiveEntity = nullptr;
}

UObject* AQueue::CycleNext()
{
    UObject* NextEntity = List[CurrentIndex];
   
    if(CurrentIndex >= List.Num() - 1)
        CurrentIndex = 0;
    else
        CurrentIndex++;
    
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

UObject* ATurnBasedQueue::CreateTurnEntity(const FName Name)
{
    return NewObject<ATurnEntity>(this, Name);
}

UObject* ATurnBasedQueue::CreateTurnEntity(const FName Name, const uint32 TurnOrder, const FGameStats &NumberOfMoves)
{
    ATurnEntity* NewEntity = Cast<ATurnEntity>(CreateTurnEntity(Name));
    NewEntity->SetTurnOrder(TurnOrder);
    NewEntity->InitMovement(NumberOfMoves);
    
    return NewEntity;
}

void ATurnBasedQueue::CreateFromNames(TArray<FName> ListOfNames /*  = TArray<FName>() */ )
{
    TArray<UObject*> NewQueueList;
    
    NewQueueList.Add(CreateTurnEntity("Player"));
    
    if(ListOfNames.Num() != 0)
    {
        for(FName Entity : ListOfNames)
        {
            NewQueueList.Add(CreateTurnEntity(Entity));
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
        if(ATurnEntity* TurnEntity = Cast<ATurnEntity>(Entity))
        {
            SortNumData SortingData(TurnEntity, TurnEntity->GetTurnOrder());
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
