// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnEntity.generated.h"

class UTurnMovement;
class AQueue;


/**
 * An entity who has been added to the turn queue
 */
UCLASS()
class PROJECTODIMH_API ATurnEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnEntity();
    
    /** The beginning of an entity's turn */
    void StartTurn();
    
    /** Finish the turn of the entity and assign remaining moves to 0 */
    void EndTurn();
    
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

};
