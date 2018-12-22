// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridEvent.h"
#include "ProjectOdimh.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Sound/SoundCue.h"






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
    Cast<UPOdimhGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->SaveGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One);
    
    if(Grid->DefaultStateChangeCue) UGameplayStatics::PlaySound2D(GetWorld(), Grid->DefaultStateChangeCue);
}
