// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClassInterface/PickHandlerInterface.h"
#include "GridPlayerController.generated.h"

class USoundCue;
/**
 * The GridPlayerController handles player input and communicate them to the Grid and Tile objects
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTODIMH_API AGridPlayerController : public APlayerController, public IPickHandlerInterface
{
	GENERATED_BODY()
	
public:
    AGridPlayerController();
    
    UFUNCTION(BlueprintPure)
    virtual class UActorPickHandlerComponent* GetPickHandler() override;
    
    virtual void NotifyPick(AActor* Actor, UActorPickHandlerComponent* PickHandler) override;
    
    // InputComponent setups
    virtual void SetupInputComponent() override;
    
    /** Start the process of a touch event */
    void BeginTouch(ETouchIndex::Type FingerIndex, FVector Location);
    /** End the process of a touch event */
    void EndTouch(ETouchIndex::Type FingerIndex, FVector Location);

    AActor* GetLastTouched();
    
protected:
    UPROPERTY(BlueprintReadOnly)
    class UActorPickHandlerComponent* TileHandlerComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* PickCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* ReleaseCue;
    
private:
    class UPlayerInputEvent* InputEvent;
    
};