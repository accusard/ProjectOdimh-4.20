// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "PlayerInputEvent.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "POdimhGameInstance.h"
#include "Entities/Game/Tile.h"
#include "Entities/Game/Grid.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Player/Match3Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TurnMovement.h"



const bool UPlayerInputEvent::IsCallerValid()
{
    if(AMatch3Controller* Caller = Cast<AMatch3Controller>(GetCaller()))
        return true;
    else
        return Super::IsCallerValid();
}

void UPlayerInputEvent::Process()
{
    if(AGrid* Grid = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGrid())
    {
        if(AActor* Actor = Cast<AMatch3Controller>(GetCaller())->GetTouchedActor())
        {
            ATile* Tile = Cast<ATile>(Actor);
            NotifyGridPickTile(Grid, Tile);
        }
        else
            NotifyGridReleaseTile(Grid);
    }
}



void UPlayerInputEvent::NotifyGridPickTile(AGrid* Grid, ATile* TilePicked)
{
    UTurnMovement* MoveLimit = TilePicked->FindComponentByClass<UTurnMovement>();
    Grid->SelectTile(TilePicked, MoveLimit);
}

void UPlayerInputEvent::NotifyGridReleaseTile(AGrid* Grid)
{
    Grid->ReleaseSelectedTile();
}
