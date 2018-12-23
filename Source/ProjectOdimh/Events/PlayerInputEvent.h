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
    virtual void OnEventStart() override;
    
private:
    void NotifyTouch(AGrid* Grid, class ATile* TilePicked);
    void NotifyRelease(AGrid* Grid);
    
};
