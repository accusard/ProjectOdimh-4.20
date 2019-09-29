// Copyright 2017-2018 Vanny Sou. All Rights Reserved.


#include "RandomGridController.h"
#include "Entities/Game/Tile.h"


EDirection ARandomGridController::GetRandomDirection()
{
    const int32 Max = (int32)EDirection::MaxDir - 1;
    
    EDirection Direction = static_cast<EDirection>(FMath::RandRange(0, Max));
    
    return Direction;
    
}

void ARandomGridController::HandlePick(AActor* PickedTile)
{
    Super::HandlePick(PickedTile);
    
    const EDirection& RandomDirection = GetRandomDirection();
}


