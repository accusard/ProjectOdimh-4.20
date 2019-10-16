// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameFramework/Actor.h"
#include "Utilities/FGameStats.h"
#include "ParticipantTurn.generated.h"

class UGameEvent;

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
    
    void Init(const FString& Name, class AGameModeBase* GameMode, const FGameStats &SetNumActions, AController* SetGridController);
    
    void Reset() override;
    
    AController* GetGridController() const;
    
    class UActionTurnBasedComponent* GetActionComponent() const;
    
    void Execute(const FMatch3GameAction& Action, UGameEvent* GameTurn);
    
    void NotifyActionsDepleted(UGameEvent* TurnEvent, const bool bSkipNotifyGameModeOfEndTurn);
        
    const uint32 GetRemainingActions() const;
    
    UFUNCTION(BlueprintPure, Category="Identifier")
    const FString& GetDisplayName() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category="Identifier")
    FString DisplayName;

private:
    UPROPERTY(VisibleAnywhere, Category="Actions")
    class UActionTurnBasedComponent* ActionComponent;
    
    AController* GridController;
};
