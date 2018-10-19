// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Events/BaseEvent.h"
#include "GameEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * DEPRECATED
 */
class PROJECTODIMH_API IGameEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION()
    virtual void Process(UBaseEvent* Event);
};
