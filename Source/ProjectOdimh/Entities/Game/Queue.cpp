// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Queue.h"
#include "Entities/Game/TurnParticipant.h"
#include "PODimhGameInstance.h"



AQueue::AQueue()
{
    CurrentIndex = 0;
    PrimaryActorTick.bCanEverTick = false;
    ActiveParticipant = nullptr;
}

UObject* AQueue::CycleNext()
{
    UObject* NextEntity = List[CurrentIndex];
   
    if(CurrentIndex >= List.Num() - 1)
        CurrentIndex = 0;
    else
        CurrentIndex++;
    
    ActiveParticipant = NextEntity;
    return NextEntity;
}

UObject* AQueue::GetActiveParticipant() const
{
    return ActiveParticipant;
}

const int32 AQueue::GetNum() const
{
    return List.Num();
}

void AQueue::AddToList(UObject* ObjectToAdd)
{
    if(ActiveParticipant == nullptr)
        ActiveParticipant = ObjectToAdd;
    
    List.Add(ObjectToAdd);
}

void AQueue::EmptyList()
{
    ActiveParticipant = nullptr;
    List.Empty();
}

void AQueue::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
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
