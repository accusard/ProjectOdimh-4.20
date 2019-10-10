// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Components/ActorComponent.h"
#include "Utilities/FGameStats.h"
#include "ActionTurnBasedComponent.generated.h"

const int INIT_MAX_ACTIONS = 3;

/**
 * A component that handles the turn-based actions of an actor by the number of acts it can make
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UActionTurnBasedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionTurnBasedComponent();

    void Init(class AGameModeBase* SetMode, const FGameStats& MaxAction);
    
    const bool Execute(const FAction& Action);
    
    /** Finish the turn of the entity and assign remaining actions to 0 */
    void NotifyActionsDepleted();
    
    void ResetActions();
    
    /** Reduce number of action by an integer */
    void ConsumeActionCount(const int32 Amount);
    
    /** Restore the number of actions */
    void RestoreActionMax();
    
    /** The available number of unit an entity can make per turn */
    UPROPERTY(EditAnywhere, Category="Actions Per Turn")
    FGameStats ActionCount;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    AGameModeBase* GameMode;
    FAction LastActionCommitted;
};
