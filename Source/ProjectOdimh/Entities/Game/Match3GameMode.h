// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Gametypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Match3GameMode.generated.h"

const int8 INIT_BASE_SCORE_MULTIPLIER = 1;

class AGrid;
class UGameEvent;
class ATurnParticipant;

/**
 * The mode for a Match3 game. Tracks a turn-based puzzle game.
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

    const bool ParticipantsBlueprintIsValid();
    
    const bool LoadParticipantsFromBlueprint();
    
    const bool LoadParticipants(USaveGame* Data);
    
    void SaveParticipants(USaveGame* Data);
    
    TMap<uint32, ATurnParticipant*>& GetParticipants();
    
    /** Add to the score */
    UFUNCTION(BlueprintCallable)
    void AddScore(const int32 Score);
    
    /** Get the current score of the game */
    UFUNCTION(BlueprintPure)
    const int GetCurrentScore();
    
    void SetCurrentScore(const int32 Score);
    
    const bool TryLoadGame(const FString &SlotName, const int32 PlayerIndex);
    
    const bool StartNewGame();
    
    ATurnParticipant* StartRound(const uint32 ParticipantTurnNum);
    void EndRound();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnRoundStart();
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnRoundEnd();
    
    ATurnParticipant* GetCurrentParticipant() const;
    
    ATurnParticipant* NewParticipant(TSubclassOf<ATurnParticipant> Blueprint, AGameModeBase* GameMode);
    ATurnParticipant* NewParticipant(const FName Name, AGameModeBase* GameMode, const struct FGameStats &NumberOfActions, AController* GridController);
    
    void ExecuteAction(ATurnParticipant* Participant, const FAction& Action);
    
protected:
    
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere)
    TMap<uint32, TSubclassOf<ATurnParticipant>> ParticipantsBlueprint;
    
    UFUNCTION(BlueprintCallable)
    void HandleTilesSwapped(ATile* DynamicTile, ATile* StaticTile);
    
    void HandleCurrentParticipantSwappedTiles();
    
private:
    UPROPERTY()
    TMap<uint32, ATurnParticipant*> Participants;
    
    ATurnParticipant* CurrentParticipant;
    
    UGameEvent* GameRound;

    
};
