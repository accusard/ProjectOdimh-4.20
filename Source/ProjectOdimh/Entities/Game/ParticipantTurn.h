// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "ParticipantTurn.generated.h"



/**
 * A  participant  contain the GridController that manipulate the game board on its turn based on actions available
 */
UCLASS()
class PROJECTODIMH_API AParticipantTurn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticipantTurn();
    
    void Init(class AGameModeBase* GameMode, const FGameStats &SetNumActions, AController* SetGridController);
    
    void Reset() override;
    
    AController* GetGridController() const;
    
    void StartTurn(class APOdimhGameState* State);
    
    UFUNCTION()
    void ReceiveActorReleasedNotification(AGameModeBase* Mode, AActor* Actor);
    
    void EndTurn();
    
    const bool IsTurnPending() const;
    
    class UActionTurnBasedComponent* GetActionComponent() const;
    
    void Execute(const FMatch3GameAction& Action);
    
    void NotifyActionsDepleted(AGameModeBase* Mode, const bool bEndTurnNow);
        
    const uint32 GetRemainingActions() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, Category="Actions")
    class UActionTurnBasedComponent* ActionComponent;
    
    AController* GridController;
    APawn* DefaultPawn;
    class UGameEvent* Turn;
};
