// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TileHandlingInterface.h"
#include "Components/ActorPickHandlerComponent.h"
#include "Entities/Game/Tile.h"
#include "Events/BaseEvent.h"

// Add default functionality here for any ITileHandlingInterface functions that are not pure virtual.





AActor* ITileHandlingInterface::GetLastGrab(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorLastPicked;
}

AActor* ITileHandlingInterface::GetTilePicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked;
}

AActor* ITileHandlingInterface::GrabTile(AActor* Controller, const FHitResult& Hit, UActorPickHandlerComponent* Comp)
{
    if(Cast<ITileHandlingInterface>(Controller) && Controller->FindComponentByClass(Comp->GetClass()))
    {
        if(ATile* Tile = Cast<ATile>(Hit.GetActor()))
        {
            Comp->ActorLastPicked = Tile;
            Comp->ActorPicked = Tile;
            Execute_OnPickTile(Controller, Hit.ImpactPoint);
        }
        return GetLastGrab(Comp);
    }
    
    return nullptr;
}

const bool ITileHandlingInterface::IsTilePicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked ? true : false;
}

void ITileHandlingInterface::OnReleaseTile_Implementation(UActorPickHandlerComponent* Comp)
{
    if(Comp->ActorPicked)
    {
        Comp->NotifyReleasePickedActor();
    }
}
