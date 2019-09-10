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
#include "Components/ActionTB.h"




void UPlayerInputEvent::OnEventStart()
{
    if(AGrid* Grid = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGrid())
    {
        if(AActor* Actor = Cast<AMatch3Controller>(GetOuter())->GetTouchedActor())
        {
            ATile* Tile = Cast<ATile>(Actor);
            NotifyTouch(Grid, Tile);
        }
        else
            NotifyRelease(Grid);
    }
}

void UPlayerInputEvent::RegisterInput(ETouchIndex::Type FingerIndex, const FVector& Location)
{
    TouchData.InputIndex = (int)FingerIndex;
    TouchData.Location = Location;
}


void UPlayerInputEvent::NotifyTouch(AGrid* Grid, ATile* TilePicked)
{
    UActionTB* MoveLimit = TilePicked->FindComponentByClass<UActionTB>();
    Grid->PickTile(TilePicked, MoveLimit);
}

void UPlayerInputEvent::NotifyRelease(AGrid* Grid)
{
    Grid->ReleasePickedTile();
}
