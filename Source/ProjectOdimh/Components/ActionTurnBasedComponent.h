// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utilities/FGameStats.h"
#include "ActionTurnBasedComponent.generated.h"

const int INIT_MAX_MOVES = 3;

/**
 * A component that handles the turn-based actions of an actor by the number of acts it can make per round
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UActionTurnBasedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionTurnBasedComponent();

    /** Set the maximum action that an entity can do per turn */
    void InitActionsPerTurn(const uint32 Max);
    
    /** Reduce number of action by an integer */
    void Consume(const int32 Amount);
    
    /** Restore the number of actions */
    void Restore();
    
    /** The available number of unit an entity can make per turn */
    UPROPERTY(EditAnywhere, Category="Actions Per Turn")
    FGameStats ActionCount;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
