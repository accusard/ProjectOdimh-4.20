// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UActionTB;
class AQueue;
class UGameEvent;

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
    
    const bool IsTurnPending() const;
    
    /** Sets the queue position of this entity but does not sort the turn queue */
    void SetQueuePosition(const uint32 Set);
    
    /** Return the position that this entity is at in the queue */
    const uint32 GetQueuePosition() const;
    
    /** Set the initial actions of this entity */
    void InitNumActions(const FGameStats &MaxActions);
    
    /** The maximum number of Actions an entity can make */
    const FGameStats& GetNumActions() const;

    void ConsumeAction(const uint32 Amt);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    /** Keep track of the number of Actions this entity can make per round */
    FGameStats NumActions;

    /** The order in which this entity can take its turn */
    UPROPERTY(EditAnywhere, Category="Turn Order")
    uint32 QueuePosition;
    
    UGameEvent* GameTurn;
};
