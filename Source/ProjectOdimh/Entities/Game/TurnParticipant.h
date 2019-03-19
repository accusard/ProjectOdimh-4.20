// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UTurnMovement;
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
    
    /** Finish the turn of the entity and assign remaining moves to 0 */
    void EndTurn();
    
    /** Sets the queue position of this entity */
    void SetTurnOrder(const uint32 Set);
    
    /** Return the position that this entity is at in the queue */
    const uint32 GetTurnOrder() const;
    
    /** Set the initial movement of this entity */
    void InitMovement(const FGameStats &Moves);
    
    /** Return the component that tracks the remaining number of move for this entity*/
    const uint32 GetRemainingMoves() const;
    
    /** The maximum number of moves an entity can make */
    const uint32 GetMaxMoves() const;
    
    /** Check for remaining moves is 0 */
    const bool HasFinishMoving() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    /** Keep track of the number of moves this entity can make per round */
    UTurnMovement* Movement;

    /** The order in which this entity can take its turn */
    UPROPERTY()
    uint32 TurnOrder;
};
