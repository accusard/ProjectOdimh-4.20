// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridPlayerController.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ActorPickHandlerComponent.h"
#include "Events/PlayerInputEvent.h"
#include "Events/TurnEvent.h"
#include "POdimhGameInstance.h"


AGridPlayerController::AGridPlayerController()
{
    TileHandlerComponent = CreateDefaultSubobject<UActorPickHandlerComponent>("Tile Handler");
    TileHandlerComponent->RegisterComponent();
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        PickCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
}

UActorPickHandlerComponent* AGridPlayerController::GetPickHandler()
{
    return TileHandlerComponent;
}

void AGridPlayerController::NotifyPick(AActor* Actor, UActorPickHandlerComponent* PickHandler)
{
    PickHandler->SetPlayerControlled();
    // no need to do anything here as PlayerInput will handle the tile
}

void AGridPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    InputComponent->BindTouch(IE_Pressed, this, &AGridPlayerController::BeginTouch);
    InputComponent->BindTouch(IE_Released, this, &AGridPlayerController::EndTouch);
    
}

void AGridPlayerController::BeginTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if(TileHandlerComponent)
    {
        FHitResult Hit = FHitResult();
        
        if(GetHitResultUnderFinger(FingerIndex, ECollisionChannel::ECC_Visibility, false, Hit))
        {
            if(GrabActor(this, Hit, TileHandlerComponent))
            {
                if(InputEvent && !InputEvent->IsPendingKill())
                    InputEvent->MarkPendingKill();
                
                InputEvent = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->NewEvent<UPlayerInputEvent>(this, "Player Input Event", true);
            }
        }
    }
}

void AGridPlayerController::EndTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if(InputEvent)
    {
        InputEvent->End();
    }
}

AActor* AGridPlayerController::GetLastTouched()
{
    AActor* LastTouched = Cast<IPickHandlerInterface>(this)->GetLastGrab(TileHandlerComponent);
    return LastTouched;
}
