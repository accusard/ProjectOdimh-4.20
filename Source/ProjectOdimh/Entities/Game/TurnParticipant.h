// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/GridEventInterface.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UActionTurnBasedComponent;
class AQueue;

/**
 * An entity who has been added to the turn queue
 */
UCLASS()
class PROJECTODIMH_API ATurnParticipant : public AActor, public IGridEventInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnParticipant();
    
    void Init(const uint32 TurnPosition, class AGameModeBase* GameMode, const FGameStats &SetNumActions, AController* Set);
    
    void Reset() override;
    
    /** Sets the queue position of this entity but does not sort the turn queue */
    void SetQueuePosition(const uint32 Set);
    
    /** Return the position that this entity is at in the queue */
    const uint32 GetQueuePosition() const;
    
    /** Set the initial actions of this entity */
    void InitNumActions(const FGameStats &MaxActions);
    
    /** The maximum number of Actions an entity can make */
    const FGameStats& GetNumActions() const;

    void ConsumeAction(const uint32 Amt);
    
    AController* GetController() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    /** Keep track of the number of Actions this entity can make per round */
    FGameStats NumActions;

    /** The order in which this entity can take its turn */
    UPROPERTY(EditAnywhere, Category="Turn Order")
    uint32 QueuePosition;
    
    class UActionTurnBasedComponent* ActionComponent;
    
    class UGridControlComponent* GridControlComponent;
    
    AController* Controller;
};
