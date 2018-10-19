// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "TileMatchListener.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "POdimhGameInstance.h"
#include "ClassInterface/GameEventInterface.h"
#include "Gametypes.h"
#include "Events/GridEvent.h"

#if !UE_BUILD_SHIPPING
#include "POdimhGameInstance.h"
#endif


// Sets default values for this component's properties
UTileMatchListener::UTileMatchListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    LastTileMatchTotal = 0;
}


// Called when the game starts
void UTileMatchListener::BeginPlay()
{
	Super::BeginPlay();
}

const int UTileMatchListener::GetLastTileMatchTotal() const
{
    return LastTileMatchTotal;
}

void UTileMatchListener::RegisterEvent(UBaseEvent* NewEvent)
{
    Super::RegisterEvent(NewEvent);

    UE_LOG(LogTemp,Warning,TEXT("Calling RegisterEvent."));
    if(UGridEvent* GridEvent = Cast<UGridEvent>(NewEvent))
    {
        GridEvent->GlobalEventManager->OnTileMatch.AddUniqueDynamic(this, &UTileMatchListener::HandleMatch);
    }
}

void UTileMatchListener::HandleMatch(const int TypeType, const int TilesNum, const int MatchNum)
{
#if !UE_BUILD_SHIPPING
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    Controller->ClientMessage("Received broadcast to HandleMatch()..");
#endif
    LastTileMatchTotal = TilesNum;
    
    if(UPOdimhGameInstance* GameInstance = Cast<UPOdimhGameInstance>(GetOwner()->GetGameInstance()))
    {
        if(TilesNum >= MatchNum)
        {
            // TODO: tile match logic
#if !UE_BUILD_SHIPPING
            Controller->ClientMessage(FString::Printf(TEXT("A successful match of %i have been made!"), TilesNum));
#endif
        }

    }
}

