// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UActionTurnBasedComponent;
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
    
    void Init(class AGameModeBase* GameMode, const FGameStats &SetNumActions, AController* Set);
    
    void Reset() override;
    
    AController* GetAssignedController() const;
    
    void StartTurn();
    
    void EndTurn();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    class UActionTurnBasedComponent* ActionComponent;
    class UGridControlComponent* GridControlComponent;
    AController* AssignedController;
    APawn* DefaultPawn;
};
