// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TileHandlingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTileHandlingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * DEPRECATED
 */
class PROJECTODIMH_API ITileHandlingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual class UTileHandlerComponent* GetComponent() = 0;
    
    /** Is use to call the blueprint function ForceRelease and register tile to grid */
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Tile Handling Interface")
    void ReleaseTile();
    
    UFUNCTION(BlueprintImplementableEvent, Category="Tile Handling Interface")
    void PickTile(const FVector& Location);
};
