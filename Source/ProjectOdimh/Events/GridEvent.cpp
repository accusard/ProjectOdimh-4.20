// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridEvent.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Sound/SoundCue.h"






void UGridEvent::HandleMatch(const int Type, const int NumTilesMatching, const int NumTilesNeeded)
{
    LastTileMatchTotal = NumTilesMatching;
    
    if(NumTilesMatching >= NumTilesNeeded)
    {
        // TODO: tile match logic
    }
}

void UGridEvent::HandleSpawn(AActor* Tile)
{

}

const bool UGridEvent::IsCallerValid()
{
    if( (Grid = Cast<AGrid>(GetCaller())) )
        return true;
    else
        return Super::IsCallerValid();
}

void UGridStateChange::OnEventStart()
{
    HandleStateChange();
}

void UGridStateChange::HandleStateChange()
{
    Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(Grid->GetWorld()))->SaveGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One);
}
