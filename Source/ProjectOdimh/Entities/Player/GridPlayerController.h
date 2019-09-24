// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClassInterface/TileHandlingInterface.h"
#include "GridPlayerController.generated.h"


/**
 * The GridPlayerController handles player input and communicate them to the Grid and Tile objects
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTODIMH_API AGridPlayerController : public APlayerController, public ITileHandlingInterface
{
	GENERATED_BODY()
	
public:
    AGridPlayerController();
    
    UFUNCTION(BlueprintPure)
    virtual class UTileHandlerComponent* GetTileHandler() override;
    
    // InputComponent setups
    virtual void SetupInputComponent() override;
    
    /** Start the process of a touch event */
    void BeginTouch(ETouchIndex::Type FingerIndex, FVector Location);
    /** End the process of a touch event */
    void EndTouch(ETouchIndex::Type FingerIndex, FVector Location);

    AActor* GetLastTouched();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UTileHandlerComponent* TileHandlerComponent;
    
private:
    class UPlayerInputEvent* InputEvent;
    
};
