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
	PrimaryComponentTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        GrabCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
    
    bPickedTile = false;
}

ATile* UTileHandlerComponent::GetLastGrab()
{
    return TileLastGrab;
}

ATile* UTileHandlerComponent::GrabTile(const FHitResult& Hit, AActor* Controller)
{
    if(ATile* Tile = Cast<ATile>(Hit.GetActor()))
    {
        TileLastGrab = Tile;
        if(ITileHandlingInterface* Interface = Cast<ITileHandlingInterface>(Controller))
            Interface->Execute_PickTile(Controller, Hit.ImpactPoint);
    }
    bPickedTile = true;
    return TileLastGrab;
}

const bool UTileHandlerComponent::IsTilePicked() const
{
    return bPickedTile;
}

void UTileHandlerComponent::SetDeltaDirection(const float Dir)
{
    DeltaDirection = Dir;
}

const float UTileHandlerComponent::GetDeltaDirection() const
{
    return DeltaDirection;
}