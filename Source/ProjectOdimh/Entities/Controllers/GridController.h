// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "ClassInterface/GridEventInterface.h"
#include "GridController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API AGridController : public AController, public IGridEventInterface
{
	GENERATED_BODY()
	
public:
    AGridController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UGridControlComponent* GridControlComponent;
    class UActionTurnBasedComponent* ActionTurnBasedComponent;
};
