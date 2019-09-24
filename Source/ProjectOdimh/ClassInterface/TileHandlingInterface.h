// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TileHandlingInterface.generated.h"

class UTileHandlerComponent;
class ATile;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTileHandlingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PROJECTODIMH_API ITileHandlingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual UTileHandlerComponent* GetTileHandler() = 0;
    virtual void NotifyPick(ATile* Tile) = 0;
    
    ATile* GetLastGrab(UTileHandlerComponent* Comp);
    ATile* GetTilePicked(UTileHandlerComponent* Comp);
    ATile* GrabTile(AActor* Controller, const FHitResult& Hit, UTileHandlerComponent* Comp);
    const bool IsTilePicked(UTileHandlerComponent* Comp);
    
protected:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Tile Handling Interface")
    void OnReleaseTile(UTileHandlerComponent* TileHandlerComp);
    void OnReleaseTile_Implementation(UTileHandlerComponent* TileHandlerComp);
    
    UFUNCTION(BlueprintImplementableEvent, Category="Tile Handling Interface")
    void OnPickTile(const FVector& Location);
};
