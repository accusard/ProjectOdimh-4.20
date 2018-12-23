// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GameEventInterface.h"
#include "Events/BaseEvent.h"

// Add default functionality here for any IGameEventInterface functions that are not pure virtual.


void IGameEventInterface::Process(UBaseEvent* Event)
{
    Event->Start();
}
