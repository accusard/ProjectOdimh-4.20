// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "POdimhGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API APOdimhGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    uint32 TurnNum;
    uint32 RoundNum;
};
