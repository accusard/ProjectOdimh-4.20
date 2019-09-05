// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UActionTB;
class AQueue;


/**
 * An entity who has been added to the turn queue
 */
UCLASS()
class PROJECTODIMH_API ATurnParticipant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnParticipant();
    
    /** The beginning of an entity's turn */
    void StartTurn();
    
    /** Finish the turn of the entity and assign remaining actions to 0 */
    void EndTurn();
    
    /** Sets the queue position of this entity but does not sort the turn queue */
    void SetQueuePosition(const uint32 Set);
    
    /** Return the position that this entity is at in the queue */
    const uint32 GetQueuePosition() const;
    
    /** Set the initial actions of this entity */
    void InitNumActions(const FGameStats &NumActions);
    
    /** The maximum number of Actions an entity can make */
    const uint32 GetMaxNumActions() const;

    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    /** Keep track of the number of max Actions this entity can make per round */
    uint32 MaxNumActions;

    /** The order in which this entity can take its turn */
    UPROPERTY(EditAnywhere, Category="Turn Order")
    uint32 QueuePosition;
};
