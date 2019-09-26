// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "ActorPickHandlerComponent.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "ClassInterface/TileHandlingInterface.h"
#include "Entities/Game/Tile.h"

// Sets default values for this component's properties
UActorPickHandlerComponent::UActorPickHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    bPickedIsControlledByPlayer = false;
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        PickCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
    
    
}

void UActorPickHandlerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if(ActorPicked && !IsActorPickedPlayerControlled())
        NotifyControllerActorPicked(GetOwner());
        
}

const bool UActorPickHandlerComponent::IsActorPickedPlayerControlled() const
{
    if(!ActorPicked)
        return false;
    
    return bPickedIsControlledByPlayer;
}

void UActorPickHandlerComponent::NotifyControllerActorPicked(AActor* Controller)
{
    if(ITileHandlingInterface* PickHandlerInterface = Cast<ITileHandlingInterface>(Controller))
        PickHandlerInterface->NotifyPick(ActorPicked, this);
}

void UActorPickHandlerComponent::NotifyReleasePickedActor()
{
    SetPlayerControlled(false);
    ActorPicked = nullptr;
}

void UActorPickHandlerComponent::SetPlayerControlled(const bool bIsControlledByPlayer /* = true */)
{
    bPickedIsControlledByPlayer = bIsControlledByPlayer;
}
