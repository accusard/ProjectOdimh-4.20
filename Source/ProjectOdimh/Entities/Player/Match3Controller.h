// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Match3Controller.generated.h"

class ATile;
class UBaseEvent;

/**
 * The Match3Controller handles player input and communicate them to the Grid object and Tile objects
 */
UCLASS()
class PROJECTODIMH_API AMatch3Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
    AMatch3Controller();
    
    // InputComponent setups
    virtual void SetupInputComponent() override;
    
    /** Is use to call the blueprint function ForceRelease (must hook function in blueprint) */
    UFUNCTION(BlueprintImplementableEvent)
    void ForceReleaseTile();
    
    /** Start the process of a touch event */
    void BeginTouch(ETouchIndex::Type FingerIndex, FVector Location);
    /** End the process of a touch event */
    void EndTouch(ETouchIndex::Type FingerIndex, FVector Location);
    /** Get a Tile object by touch */
    AActor* TouchTile(ETouchIndex::Type FingerIndex, ECollisionChannel CollisionChannel, const bool bTrace);
    
protected:
    UFUNCTION(BlueprintImplementableEvent)
    void PickTile(const FVector& Location);
    
private:
    
};
