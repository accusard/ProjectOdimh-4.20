// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PlayerInputEvent.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "POdimhGameInstance.h"
#include "Entities/Game/Tile.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Match3GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TurnMovement.h"



void UPlayerInputEvent::Process()
{
    if(ATile* Tile = SelectTile())
    {
        PlayGrabSound(Tile);
    }
}

void UPlayerInputEvent::BroadcastPlayerInput()
{
    OnPlayerInput.Broadcast();
}

void UPlayerInputEvent::PlayGrabSound(ATile* Tile)
{
    if(Tile->GrabCue) UGameplayStatics::PlaySound2D(GetWorld(), Tile->GrabCue);
}

ATile* UPlayerInputEvent::SelectTile()
{
    if(ATile* Tile = Cast<ATile>(GetOuter()))
    {
        // target is a game board select the tile
        if(AGrid* Grid = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGrid())
        {
            UTurnMovement* MoveLimit = Tile->FindComponentByClass<UTurnMovement>();
            Grid->SelectTile(Tile, MoveLimit);
        }
        
        return Tile;
    }
    
    return nullptr;
}
