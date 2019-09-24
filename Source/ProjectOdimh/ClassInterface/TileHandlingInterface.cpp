// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TileHandlingInterface.h"
#include "Components/TileHandlerComponent.h"
#include "Entities/Game/Tile.h"
#include "Events/BaseEvent.h"

// Add default functionality here for any ITileHandlingInterface functions that are not pure virtual.





ATile* ITileHandlingInterface::GetLastGrab(UTileHandlerComponent* Comp)
{
    return Comp->TileLastGrab;
}

ATile* ITileHandlingInterface::GetTilePicked(UTileHandlerComponent* Comp)
{
    return Comp->TilePicked;
}

ATile* ITileHandlingInterface::GrabTile(AActor* Controller, const FHitResult& Hit, UTileHandlerComponent* Comp)
{
    if(Cast<ITileHandlingInterface>(Controller) && Controller->FindComponentByClass(Comp->GetClass()))
    {
        if(ATile* Tile = Cast<ATile>(Hit.GetActor()))
        {
            Comp->TileLastGrab = Tile;
            Comp->TilePicked = Tile;
            Execute_OnPickTile(Controller, Hit.ImpactPoint);
        }
        return GetLastGrab(Comp);
    }
    
    return nullptr;
}

const bool ITileHandlingInterface::IsTilePicked(UTileHandlerComponent* Comp)
{
    return Comp->TilePicked ? true : false;
}

void ITileHandlingInterface::OnReleaseTile_Implementation(UTileHandlerComponent* Comp)
{
    if(Comp->TilePicked)
    {
        Comp->NotifyReleasePickedTile();
    }
}
