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
class UGameEvent;
class ATurnBasedQueue;
class ATurnParticipant;

/**
 * The mode for a Match3 game. Determine the winning and losing conditions of the game.
 * Select objects on a grid and match 3 of a kind to score points.
 */
UCLASS()
class PROJECTODIMH_API AMatch3GameMode : public AGameModeBase, public IGameEventInterface, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    // constructor
    AMatch3GameMode();
    
    virtual void Tick(float DeltaSeconds) override;
    virtual void StartPlay() override;
    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    /** Check since the round started if this is a new game */
    const bool IsNewGame() const;
    
    /** Set the state of the game as a new game so game mode can perform preinitializations of certain game elements */
    void SetNewGameState(const bool IsNewGame);
    
    /** Save the game and quit */
    UFUNCTION(BlueprintCallable)
    void SaveAndQuit(const int32 PlayerIndex);
    
    const bool CreateQueueFromBlueprint();

    /** Loads data to the queuelist */
    const bool LoadQueueListFromSave(USaveGame* Data);
    
    void SaveQueueList(USaveGame* Data);
    
    /** Sets the current board of the game */
    void SetGrid(AGrid* Board);
    
    /** Get the current game board */
    AGrid* GetGrid();
    
    ATurnBasedQueue* GetOrderQueue();
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void AddScore(const int32 Score);
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    void SetCurrentScore(const int32 Score);
    
    const bool TryLoadGame(const FString &SlotName, const int32 PlayerIndex);
    
    void StartNewGame(const int32 PlayerIndex);
    
    ATurnParticipant* StartRound(const int32 NextParticipantIndex);
    void EndRound();
    
protected:
    /** Retrieve the value that was set in blueprint and assign it to this object's member data Grid */
    UFUNCTION(BlueprintImplementableEvent)
    void SetGameBoardFromBlueprint();
    
    virtual void BeginPlay() override;
    
    /** The current game board */
    UPROPERTY(BlueprintReadWrite)
    AGrid* Grid;
    
    /** Keep track of the turn-based queue */
    UPROPERTY(BlueprintReadOnly)
    ATurnBasedQueue* OrderQueuePtr;
    
private:
    /** GAME STATES */
    /** Tracks the current score of the game */
    UPROPERTY()
    int32 CurrentScore;
    
    /** Flag to determine if the current game have been started completely new and not loaded from save */
    bool bNewGame;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<ATurnBasedQueue> OrderQueueBP;
    
    ATurnParticipant* CurrentParticipant;
    
    UGameEvent* GameRound;
    
    UUserWidget* TurnWidget;
    
};
