// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridController.h"
#include "PaperSpriteComponent.h"
#include "Components/ActorPickHandlerComponent.h"
#include "Components/ActionTurnBasedComponent.h"
#include "ClassInterface/PickHandlerInterface.h"
#include "Entities/Game/Tile.h"


AGridController::AGridController()
{
    TileHandlerComponent = CreateDefaultSubobject<UActorPickHandlerComponent>("Tile Handler Component");
}

// Called every frame
void AGridController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UActorPickHandlerComponent* AGridController::GetPickHandler()
{
    return TileHandlerComponent;
}

void AGridController::NotifyPick(AActor* Actor, UActorPickHandlerComponent* PickHandler)
{
#if !UE_BUILD_SHIPPING
    UE_LOG(LogTemp,Warning,TEXT("GridController Recieved NotifyPick. Now do something with %s."), *Actor->GetName());
#endif
}

void AGridController::MoveTile(ATile* Tile, const EDirection& Dir, const float Delta)
{
    float Direction;
    
    if(Dir == EDirection::Up || Dir == EDirection::Down)
    {
        Direction = FMath::Clamp<float>(Delta, 0, Tile->SpriteSize.Y / 2);
    }
    else
    {
        Direction = FMath::Clamp<float>(Delta, 0, Tile->SpriteSize.X / 2);
    }
    
    switch(Dir)
    {
        case EDirection::Up:
        {
            Direction = -Direction;
            break;
        }
        case EDirection::Down:
        {
            break;
        }
        case EDirection::Left:
        {
            Direction = -Direction;
            break;
        }
        case EDirection::Right:
        {
            break;
        }
    }
    
    const FVector& TileLocation = Tile->GetActorLocation();
    FHitResult Hit;
    Hit.Actor = Tile;
    Hit.ImpactPoint = TileLocation;
    Cast<IPickHandlerInterface>(this)->GrabActor(this, Hit, TileHandlerComponent);
}
