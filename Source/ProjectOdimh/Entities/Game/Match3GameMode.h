// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Gametypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Match3GameMode.generated.h"

const int8 INIT_BASE_SCORE_MULTIPLIER = 1;

class AGrid;
class UGameEvent;
class AParticipantQueue;
class ATurnParticipant;

/**
 * The mode for a Match3 game. Determine the winning and losing conditions of the game.
 * Select objects on a grid and match 3 of a kind to score points.
 */
UCLASS()
class PROJECTODIMH_API AMatch3GameMode : public AGameModeBase, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    // constructor
    AMatch3GameMode();
    
    virtual void Tick(float DeltaSeconds) override;
    virtual void StartPlay() override;
    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
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
    
    AParticipantQueue* GetOrderQueue();
    
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
    
    ATurnParticipant* GetCurrentParticipant() const;
    
protected:
    
    virtual void BeginPlay() override;
    
    /** The current game board */
    UPROPERTY(BlueprintReadWrite)
    AGrid* Grid;
    
    /** Keep track of the turn-based queue */
    UPROPERTY(BlueprintReadOnly)
    AParticipantQueue* OrderQueuePtr;
    
    UPROPERTY(EditAnywhere)
    TMap<uint32, TSubclassOf<ATurnParticipant>> TurnQueue;
    
private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<AParticipantQueue> OrderQueueBP;
    
    ATurnParticipant* CurrentParticipant;
    
    UGameEvent* GameRound;

    
};
