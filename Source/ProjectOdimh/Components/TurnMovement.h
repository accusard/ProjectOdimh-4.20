// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utilities/FGameStats.h"
#include "TurnMovement.generated.h"

const int INIT_MAX_MOVES = 3;

/**
 * A component that handles the turn-based actions of an actor by the number of acts it can make per round
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UTurnMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurnMovement();

    /** Set the maximum moves that an entity can do per turn */
    void InitMovesPerTurn(const uint32 Max);
    
    /** Reduce number of moves by an integer */
    void ConsumeMoves(const int32 Amount);
    
    /** Restores the number of moves and register its old position */
    void RestoreMoves();
    
    /** The available number of unit an entity can make per turn */
    UPROPERTY(EditAnywhere, Category="Moves Per Turn")
    FGameStats Moves;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
