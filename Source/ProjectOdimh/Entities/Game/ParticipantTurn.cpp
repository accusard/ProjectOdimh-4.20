// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#include "ParticipantTurn.h"
#include "POdimhGameInstance.h"
#include "POdimhGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Controllers/Player/GridPlayerController.h"
#include "Components/ActionTurnBasedComponent.h"
#include "Events/GameEvent.h"


// Sets default values
AParticipantTurn::AParticipantTurn()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    ActionComponent = CreateDefaultSubobject<UActionTurnBasedComponent>("Action Component");
    
    
}

void AParticipantTurn::Init(const FString& Name, const FGameStats &SetNumActions, AController* SetController)
{
    DisplayName = Name;
    ActionComponent->Init(SetNumActions);
    GridController = SetController;
    
}

void AParticipantTurn::Reset()
{
    ActionComponent->ResetActions();
}

// Called when the game starts or when spawned
void AParticipantTurn::BeginPlay()
{
	Super::BeginPlay();
}

AController* AParticipantTurn::GetGridController() const
{
    return GridController;
}

void AParticipantTurn::NotifyActionsDepleted()
{
    UE_LOG(LogTemp, Warning, TEXT("TODO: Actions depleted. Notify GridController."));
}

const FString& AParticipantTurn::GetDisplayName() const
{
    return DisplayName;
}

void AParticipantTurn::ForceReleaseTile()
{
    UE_LOG(LogTemp, Warning, TEXT("TODO: call this->grid controller interface to OnReleaseActor"));
    if(AGridPlayerController* Controller = Cast<AGridPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
    {
        Controller->ForceRelease();
    }
}
