// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Events/BaseEvent.h"
#include "GridEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGridEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * DEPRECATED
 */
class PROJECTODIMH_API IGridEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    
    
    /** Is use to call the blueprint function ForceRelease and register tile to grid */
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void ReleaseTile();
    
    UFUNCTION(BlueprintImplementableEvent)
    void PickTile(const FVector& Location);
};
