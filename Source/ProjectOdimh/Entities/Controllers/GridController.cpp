// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridController.h"
#include "PaperSpriteComponent.h"
#include "Components/GridControlComponent.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Entities/Game/Tile.h"


AGridController::AGridController()
{
    GridControlComponent = CreateDefaultSubobject<UGridControlComponent>("Grid Control Component");
}

// Called every frame
void AGridController::Tick(float DeltaTime)
{
    if(GridControlComponent->IsTilePicked())
    {
        // TODO: update tile location
    }
    
    Super::Tick(DeltaTime);
}

UGridControlComponent* AGridController::GetComponent()
{
    return GridControlComponent;
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
    GridControlComponent->GrabTile(Hit, this);
    GridControlComponent->SetDeltaDirection(Direction);
}
