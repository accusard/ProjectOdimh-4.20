// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Entities/Game/TurnParticipant.h"
#include "Queue.generated.h"



/**
 * A list of entities that can be cycled through and loops in a ringed fashion
 */
UCLASS(Blueprintable)
class PROJECTODIMH_API AQueue : public AInfo
{
	GENERATED_BODY()
	
public:
    // constructor
    AQueue();
    
    /** Add an entity to the back of the list */
    void AddToList(UObject* ObjectToAdd);
    
    void EmptyList();
    
    /** Cycle to the next entity on the list. Will loop back to the first element after the last */
    UFUNCTION(BlueprintCallable, Category="Cycling")
    UObject* CycleNext();
    
    /** Returns the total in the queue list */
    const int32 GetNumObjectsInList() const;
    
    UFUNCTION(BlueprintCallable, Category="Index")
    UObject* GetFromIndex(const int32 index) const;
    
    void SetCurrentIndex(const int32 index);
    const int32 GetCurrentIndex() const;
    
protected:
    virtual void BeginPlay() override;
    
    /** A list of entities in queue */
    UPROPERTY(EditAnywhere, Category="Edit Queue List")
    TArray<UObject*> List;
    
    /** The current position of the queue when cycling */
    UPROPERTY(BlueprintReadOnly, Category="Index")
    int32 Index;
};

/**
 * A list of named entities used to create turn based behavior
 */
UCLASS()
class PROJECTODIMH_API ATurnBasedQueue : public AQueue
{
    GENERATED_BODY()
    
public:
    /** Create a queue list from a list of names.  */
    void CreateFromNames(TArray<FName> ListOfNames = TArray<FName>());
    
    /** Create a queue list from a TArray of objects */
    void CreateFromObjects(TArray<UObject*> QueList);
    
    /** Sort the entities in ascending order */
    void SortTurnOrder();
    
    /** Return a new object of type ATurnParticipant */
    UObject* AddParticipant(const FName Name);
    UObject* AddParticipant(const FName Name, const uint32 PositionInQueue, const FGameStats &NumberOfMoves);
};

struct SortNumData
{
    SortNumData(UObject* Obj, int SortingOrder)
    {
        ObjPtr = Obj;
        Order = SortingOrder;
    }
    const bool operator==(const SortNumData &Other)
    {
        return Order == Other.Order;
    }
    const bool operator!=(const SortNumData &Other)
    {
        return Order != Other.Order;
    }
    const bool operator<(const SortNumData &Other)
    {
        return Order < Other.Order;
    }
    const bool operator>(const SortNumData &Other)
    {
        return Order > Other.Order;
    }
    const bool operator<=(const SortNumData &Other)
    {
        return Order <= Other.Order;
    }
    const bool operator>=(const SortNumData &Other)
    {
        return Order >= Other.Order;
    }
    
    UObject* ObjPtr;
    int Order;
};

class MySortingClass
{

public:
    TArray<SortNumData> MergeSort(const TArray<SortNumData> &M)
    {
        // If the list has only one element, return the list and terminate. (Base case)
        if(M.Num() <= 1) return M;

        // Split the list into two halves that are as equal in length as possible. (Divide)
        int ArrayHalf = M.Num() / 2;
        TArray<SortNumData> Left;
        TArray<SortNumData> Right;
        for(int i = 0; i < ArrayHalf; i++)
        {
            Left.Add(M[i]);
            UE_LOG(LogTemp,Warning,TEXT("ArrayHalf: %i"), i);
        }
        for(int i = ArrayHalf; i<= M.Num(); i++)
        {
            Right.Add(M[i]);
            UE_LOG(LogTemp,Warning,TEXT("ArrayHalf: %i"), i);
        }
        // Using recursion, sort both lists using mergesort. (Conquer)
        Left = MergeSort(Left);
        Right = MergeSort(Right);
        
        // Merge the two sorted lists and return the result. (Combine)
        TArray<SortNumData> Sorted = Merge(Left,Right);
        return Sorted;
    }
    
    TArray<SortNumData> Merge(TArray<SortNumData> &Left, TArray<SortNumData> &Right)
    {
        TArray<SortNumData> Result;
        int LeftIndex = 0, RightIndex = 0;
        while(LeftIndex < Left.Num() && RightIndex < Right.Num())
        {
            if(Left[LeftIndex] <= Right[RightIndex])
            {
                Result.Add(Left[LeftIndex]);
                LeftIndex += 1;
            }
            else
            {
                Result.Add(Right[RightIndex]);
                RightIndex += 1;
            }
        }
        return Result;
    }
private:
    TArray<UObject*> SortedArray;
    
};
