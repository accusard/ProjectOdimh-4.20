// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "PlayerInputEvent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerInputDelegate);


class ATile;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UPlayerInputEvent : public UBaseEvent
{
	GENERATED_BODY()
	
public:
    virtual void Process() override;
    
    void BroadcastPlayerInput();
    
    void PlayGrabSound(ATile* Tile);
	
    // delegates
    UPROPERTY(BlueprintAssignable)
    FPlayerInputDelegate OnPlayerInput;
    
private:
    ATile* SelectTile();
    
};
