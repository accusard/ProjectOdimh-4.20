// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Match3Controller.h"
#include "Engine/World.h"
#include "Entities/Game/Grid.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Game/Match3GameMode.h"
#include "Events/PlayerInputEvent.h"
#include "Events/TurnEvent.h"
#include "POdimhGameInstance.h"


AMatch3Controller::AMatch3Controller()
{
    
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
        Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->Create(NewObject<UPlayerInputEvent>(this));
}

void AMatch3Controller::EndTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    AGrid* Grid = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGrid();
    
    if(Grid)
        Grid->ReleaseSelectedTile();
    
    TouchedActor = nullptr;
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
