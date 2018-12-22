// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "PlayerInputEvent.generated.h"





class AGrid;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UPlayerInputEvent : public UBaseEvent
{
	GENERATED_BODY()
	
public:
    virtual const bool IsCallerValid() override;
    virtual void Process() override;
    
private:
    void NotifyGridSelectTile(AGrid* Grid, class ATile* ActorTouched);
    void NotifyGridReleaseTile(AGrid* Grid);
    
};
