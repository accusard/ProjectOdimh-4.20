// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClassInterface/GridEventInterface.h"
#include "GridPlayerController.generated.h"

class ATile;
class UBaseEvent;
class USoundCue;
/**
 * The GridPlayerController handles player input and communicate them to the Grid and Tile objects
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTODIMH_API AGridPlayerController : public APlayerController, public IGridEventInterface
{
	GENERATED_BODY()
	
public:
    AGridPlayerController();
    
    // InputComponent setups
    virtual void SetupInputComponent() override;
    
    /** Start the process of a touch event */
    void BeginTouch(ETouchIndex::Type FingerIndex, FVector Location);
    /** End the process of a touch event */
    void EndTouch(ETouchIndex::Type FingerIndex, FVector Location);

    AActor* GetLastTouched();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UGridControlComponent* GridControlComponent;
    
    class UActionTurnBasedComponent* ActionTurnBasedComponent;
    
private:
    class UPlayerInputEvent* InputEvent;
    
};
