// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Entities/Game/TurnEntity.h"
#include "Queue.generated.h"



/**
 * Tracks a list of entities in an ordered ring fashion.
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

    /** Returns the total in the queue list */
    const int32 GetNum() const;
    
    /** The current position of the queue */
    int32 Position;
    
protected:
    /** A list of entities in queue */
    UPROPERTY()
    TArray<UObject*> List;
};
