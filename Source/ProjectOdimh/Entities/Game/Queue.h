// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Entities/Game/TurnEntity.h"
#include "Queue.generated.h"



/**
 * A list of entities that can be cycled through and loops in a ringed fashion
 */
UCLASS()
class PROJECTODIMH_API AQueue : public AInfo
{
	GENERATED_BODY()
	
public:
    // constructor
    AQueue();
    
    virtual void Tick(float DeltaTime) override;
    
    /** Add an entity to the back of the list */
    void AddToList(UObject* ObjectToAdd);
    
    void EmptyList();
    
    /** Cycle to the next entity on the waiting list. Will loop back to the first element after the last */
    UObject* CycleNext();

    /** Return the currently active entity in the turn queue */
    UObject* GetActiveEntity() const;
    
    /** Returns the total in the queue list */
    const int32 GetNum() const;
    
    /** The current position of the queue */
    int32 Position;
    
protected:
    /** A list of entities in queue */
    UPROPERTY()
    TArray<UObject*> List;
    
    UPROPERTY()
    UObject* ActiveEntity;
};

/**
 * A list of named entities used to create turn based behavior
 */
UCLASS()
class PROJECTODIMH_API ATurnBasedQueue : public AQueue
{
    GENERATED_BODY()
    
public:
    /** Create a queue list from a list of names. Will always create a "Player" entity before creating the list */
    void CreateNewQueue(UObject* Outer, TArray<FName> ListOfNames = TArray<FName>());

private:
    /** Initializes the queue using a TArray of objects */
    void Init(TArray<UObject*> QueList);
    
    /** Return a new object of type ATurnEntity */
    UObject* CreateTurnEntity(UObject* Outer, const FName Name);
};
