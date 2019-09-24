// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridPlayerController.h"
#include "Engine/World.h"
#include "Components/TileHandlerComponent.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/PlayerInputEvent.h"
#include "Events/TurnEvent.h"
#include "POdimhGameInstance.h"


AGridPlayerController::AGridPlayerController()
{
    TileHandlerComponent = CreateDefaultSubobject<UTileHandlerComponent>("Tile Handler Component");
}

UTileHandlerComponent* AGridPlayerController::GetComponent()
{
    return TileHandlerComponent;
}

void AGridPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    InputComponent->BindTouch(IE_Pressed, this, &AGridPlayerController::BeginTouch);
    InputComponent->BindTouch(IE_Released, this, &AGridPlayerController::EndTouch);
    
}

void AGridPlayerController::BeginTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    FHitResult Hit = FHitResult();
    
    if(GetHitResultUnderFinger(FingerIndex, ECollisionChannel::ECC_Visibility, false, Hit))
    {
        if(TileHandlerComponent->GrabTile(Hit, this))
        {
            if(InputEvent && !InputEvent->IsPendingKill())
                InputEvent->MarkPendingKill();
            
            InputEvent = Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->NewEvent<UPlayerInputEvent>(this, "Player Input Event", true);
            InputEvent->RegisterInput(FingerIndex, Location);
        }
    }
}

void AGridPlayerController::EndTouch(ETouchIndex::Type FingerIndex, FVector Location)
{
    if(InputEvent)
    {
        InputEvent->RegisterInput(FingerIndex, Location);
        InputEvent->End();
    }
}

AActor* AGridPlayerController::GetLastTouched()
{
    return TileHandlerComponent->GetLastGrab();
}
