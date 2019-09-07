// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3Controller.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Entities/Game/Grid.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Game/Match3GameMode.h"
#include "Events/PlayerInputEvent.h"
#include "Events/TurnEvent.h"
#include "POdimhGameInstance.h"


AMatch3Controller::AMatch3Controller()
{
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultGrabSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_173_Cue.UI_Neutral_173_Cue'"));
    
    static ConstructorHelpers::FObjectFinder<USoundCue> DefaultReleaseSoundCue(TEXT("SoundCue'/Game/The_Future_Is_Now/cues/1_Neutral/UI_Neutral_205_Cue.UI_Neutral_205_Cue'"));
    
    if(DefaultGrabSoundCue.Object)
        GrabCue = DefaultGrabSoundCue.Object;
    
    if(DefaultReleaseSoundCue.Object)
        ReleaseCue = DefaultReleaseSoundCue.Object;
}

void AMatch3Controller::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    InputComponent->BindTouch(IE_Pressed, this, &AMatch3Controller::BeginTouch);
    InputComponent->BindTouch(IE_Released, this, &AMatch3Controller::EndTouch);
    
}

void AMatch3Controller::BeginTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if( (TouchedActor = TouchTile(FingerIndex, ECollisionChannel::ECC_Visibility, false)) )
    {
        UBaseEvent* Event = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->Create(NewObject<UPlayerInputEvent>(this));
        
        if(UPlayerInputEvent* PlayerEvent = Cast<UPlayerInputEvent>(Event))
            PlayerEvent->RegisterInput(FingerIndex, Location);
    }
}

void AMatch3Controller::EndTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    TouchedActor = nullptr;
    
    UBaseEvent* Event = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->Create(NewObject<UPlayerInputEvent>(this));
    
    if(UPlayerInputEvent* PlayerEvent = Cast<UPlayerInputEvent>(Event))
        PlayerEvent->RegisterInput(FingerIndex, Location);
}

AActor* AMatch3Controller::TouchTile(ETouchIndex::Type FingerIndex, ECollisionChannel CollisionChannel, const bool bTrace)
{
    FHitResult Hit = FHitResult();
    AActor* Tile = nullptr;
    
    if(GetHitResultUnderFinger(FingerIndex, CollisionChannel, bTrace, Hit))
    {
        if(ATile* SelectedTile = Cast<ATile>(Hit.GetActor()))
        {
            PickTile(Hit.ImpactPoint);
            Tile = SelectedTile;
        }
    }
    
    return Tile;
}

AActor* AMatch3Controller::GetTouchedActor()
{
    return TouchedActor;
}
