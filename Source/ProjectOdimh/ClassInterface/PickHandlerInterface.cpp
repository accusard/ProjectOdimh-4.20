// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PickHandlerInterface.h"
#include "Components/ActorPickHandlerComponent.h"
#include "Entities/Game/Tile.h"
#include "Events/BaseEvent.h"

// Add default functionality here for any IPickHandlerInterface functions that are not pure virtual.





AActor* IPickHandlerInterface::GetLastGrab(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorLastPicked;
}

AActor* IPickHandlerInterface::GetActorPicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked;
}

AActor* IPickHandlerInterface::GrabActor(AActor* InterfaceHandler, const FHitResult& Hit, UActorPickHandlerComponent* Comp)
{
    if(Cast<IPickHandlerInterface>(InterfaceHandler) && InterfaceHandler->FindComponentByClass(Comp->GetClass()))
    {
        if(ATile* Tile = Cast<ATile>(Hit.GetActor()))
        {
            Comp->ActorLastPicked = Tile;
            Comp->ActorPicked = Tile;
            Execute_OnPickActor(InterfaceHandler, Hit.ImpactPoint);
        }
        return GetLastGrab(Comp);
    }
    
    return nullptr;
}

const bool IPickHandlerInterface::IsActorPicked(UActorPickHandlerComponent* Comp)
{
    return Comp->ActorPicked ? true : false;
}

void IPickHandlerInterface::OnReleaseActor_Implementation(UActorPickHandlerComponent* Comp)
{
    if(Comp->ActorPicked)
    {
        Comp->NotifyReleasePickedActor();
    }
}
