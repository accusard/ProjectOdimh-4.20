// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GridController.h"
#include "POdimhGameInstance.h"
#include "Components/ActorPickHandlerComponent.h"




AGridController::AGridController()
{
    TileHandlerComponent = CreateDefaultSubobject<UActorPickHandlerComponent>("Tile Handler Component");
}

// Called every frame
void AGridController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGridController::BeginPlay()
{
    Super::BeginPlay();
    Cast<UPOdimhGameInstance>(GetGameInstance())->EventManager->OnActorPicked.AddDynamic(this, &AGridController::HandlePick);
}

UActorPickHandlerComponent* AGridController::GetPickHandler()
{
    return TileHandlerComponent;
}

void AGridController::HandlePick(AActor* PickedTile)
{
#if !UE_BUILD_SHIPPING
    UE_LOG(LogTemp,Warning,TEXT("GridController Recieved OnActorPicked. Now do something with %s."), *PickedTile->GetName());
#endif
}


