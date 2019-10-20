// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    
    void Init(const FString& Name, AController* SetGridController);
    
    AController* GetGridController() const;
    
    UFUNCTION(BlueprintPure, Category="Identifier")
    const FString& GetDisplayName() const;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, Category="Identifier")
    FString DisplayName;

private:
    AController* GridController;
};
