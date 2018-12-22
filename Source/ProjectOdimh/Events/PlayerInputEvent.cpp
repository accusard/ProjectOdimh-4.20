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



void UPlayerInputEvent::Process()
{
    if(AActor* Tile = Cast<AMatch3Controller>(GetCaller())->GetTouchedActor())
        NotifyGrid(Tile);
}



void UPlayerInputEvent::NotifyGrid(AActor* ActorTouched)
{
    if(AGrid* Grid = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGrid())
    {
        ATile* Tile = Cast<ATile>(ActorTouched);
        UTurnMovement* MoveLimit = ActorTouched->FindComponentByClass<UTurnMovement>();
        Grid->SelectTile(Tile, MoveLimit);
    }

}
