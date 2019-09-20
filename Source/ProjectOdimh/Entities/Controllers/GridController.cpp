// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridController.h"
#include "Components/GridControlComponent.h"
#include "Components/ActionTurnBasedComponent.h"


AGridController::AGridController()
{
    GridControlComponent = CreateDefaultSubobject<UGridControlComponent>("Grid Control Component");
    ActionTurnBasedComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Turn-Based Component");
}
