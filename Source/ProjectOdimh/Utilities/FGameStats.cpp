// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "FGameStats.h"
#include "Gametypes.h"

FGameStats::FGameStats()
{
    Remaining = 0;
    Maximum = 0;
}

FGameStats::FGameStats(const uint SetMax)
{
    // TODO: need to increase maximum value
    Maximum = FMath::Clamp<uint>(SetMax, DEFAULT_VALUE, MAXIMUM_VALUE_1000);
    Remaining = Maximum;
}

