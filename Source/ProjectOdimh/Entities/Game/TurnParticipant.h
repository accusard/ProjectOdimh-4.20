// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "TurnParticipant.generated.h"

class UActionTurnBasedComponent;
class AQueue;

/**
 * A  participant  contain the GridController that manipulate the game board on its turn based on actions available
 */
UCLASS()
class PROJECTODIMH_API ATurnParticipant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnParticipant();
    
    void Init(class AGameModeBase* GameMode, const FGameStats &SetNumActions, AController* SetGridController);
    
    void Reset() override;
    
    AController* GetGridController() const;
    
    void StartTurn(class APOdimhGameState* State);
    
    void EndTurn();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    class UActionTurnBasedComponent* ActionComponent;
    class UActorPickHandlerComponent* TileHandlerComponent;
    AController* GridController;
    APawn* DefaultPawn;
};
