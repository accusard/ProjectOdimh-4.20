// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnEntity.generated.h"

class UTurnMovement;
class AQueue;

// TODO: add function to set the round
// TODO: add function to increment turns
/**
 * An entity who has control of the current round
 */
UCLASS()
class PROJECTODIMH_API ATurnEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnEntity();
    
    void EndTurn();
    
    /** Return the component that tracks the remaining number of move for this entity*/
    UTurnMovement* GetMovement() const;
    
    const bool HasFinishMoving() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    
    /** Keep track of the number of moves this entity can make per round */
    UTurnMovement* TurnMoves;
    
    /** A reference to the current round */
    AQueue* TurnQueue;
    
    bool bMoveFinished;
};
