// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridEvent.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Sound/SoundCue.h"




void UGridEvent::BroadcastTileMatch(const int TileType, const int TilesNum, const int MatchNum)
{
    GlobalEventManager->OnTileMatch.Broadcast(TileType, TilesNum, MatchNum);
}

void UGridEvent::BroadcastStateChange()
{
    GlobalEventManager->OnGridStateChange.Broadcast();
}

void UGridEvent::BroadcastComponentSpawn(AActor* SpawnedActor, UActorComponent* Component)
{
    GlobalEventManager->OnSpawnFromComponent.Broadcast(SpawnedActor, Component);
}

const bool UGridStateChange::IsCallerValid()
{
    if( !(Grid = Cast<AGrid>(GetCaller())) )
    {
        return false;
    }
    
    return Super::IsCallerValid();
}

void UGridStateChange::Process()
{
    Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->SaveGame(CONTINUE_GAME_SLOT);
    
    if(Grid->StateChangeCue) UGameplayStatics::PlaySound2D(GetWorld(), Grid->StateChangeCue);
}
