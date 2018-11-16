// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Gametypes.h"
#include "ClassInterface/GameEventInterface.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Match3GameMode.generated.h"

const int8 INIT_BASE_SCORE_MULTIPLIER = 1;

class AGrid;
class ATile;
class AQueue;
class AState;
class UBaseEvent;

/**
 * The mode for a Match3 game. Determine the winning and losing conditions of the game.
 * Select objects on a grid and match 3 of a kind to score points.
 */
UCLASS()
class PROJECTODIMH_API AMatch3GameMode : public AGameMode, public IGameEventInterface, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    // constructor
    AMatch3GameMode();
    
    virtual void Tick(float DeltaSeconds) override;
    virtual void StartPlay() override;
    virtual void Save(USaveGame* Data) override;
    virtual const bool Load(USaveGame* Data) override;
    
    /** Save the game and quit */
    UFUNCTION(BlueprintCallable)
    void SaveAndQuit();
    
    void InitTurnQueue(TArray<UObject*> QueList);
    
    /** Create a queue list from a list of names. Will always create a "Player" entity before creating the list */
    void CreateNewTurnQueue(UObject* Outer, TArray<FName> ListOfNames = TArray<FName>());
    
    UObject* CreateTurnEntity(UObject* Outer, const FName Name);
    
    /** Sets the current board of the game */
    void SetGrid(AGrid* Board);
    
    /** Get the current game board */
    AGrid* GetGrid();
    
    AQueue* GetTurnQueue();
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void AddScore(const int32 Score);
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    void SetCurrentScore(const int32 Score);
    
protected:
    /** Retrieve the value that was set in blueprint and assign it to this object's member data Grid */
    UFUNCTION(BlueprintImplementableEvent)
    void SetGameBoardFromBlueprint();
    
    virtual void BeginPlay() override;
    
    /** The current game board */
    UPROPERTY(BlueprintReadWrite)
    AGrid* Grid;
    
private:
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;
    
    UPROPERTY()
    AQueue* TurnQueue;
};
