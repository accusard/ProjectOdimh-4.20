// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TileHandlerComponent.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "ClassInterface/TileHandlingInterface.h"
#include "Entities/Game/Tile.h"

// Sets default values for this component's properties
UTileHandlerComponent::UTileHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    bTileIsPlayerControlled = false;
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        GrabCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
    
    
}

void UTileHandlerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if(TilePicked && !TileIsPlayerControlled())
        NotifyController(GetOwner(), TilePicked);
        
}

void UTileHandlerComponent::SetPlayerControlled(const bool bPlayerControlled)
{
    bTileIsPlayerControlled = bPlayerControlled;
}

const bool UTileHandlerComponent::TileIsPlayerControlled() const
{
    return bTileIsPlayerControlled;
}

void UTileHandlerComponent::SetDeltaDirection(const float Dir)
{
    DeltaDirection = Dir;
}

const float UTileHandlerComponent::GetDeltaDirection() const
{
    return DeltaDirection;
}

void UTileHandlerComponent::NotifyController(AActor* Controller, ATile* Tile)
{
    Cast<ITileHandlingInterface>(Controller)->NotifyPick(TilePicked);
}

void UTileHandlerComponent::NotifyReleasePickedTile()
{
    TilePicked = nullptr;
    SetPlayerControlled(false);
}
