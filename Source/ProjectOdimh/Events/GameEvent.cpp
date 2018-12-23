// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GameEvent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Gametypes.h"
#include "POdimhGameInstance.h"
#include "Events/EventManager.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Game/Queue.h"








void UGameEvent::InitializeEvent()
{
    Super::InitializeEvent();
}

void UGameStart::InitializeEvent()
{
    Super::InitializeEvent();
}

void UGameStart::Process()
{
    if(!TryLoadGame(CONTINUE_GAME_SLOT, (int32)EPlayer::One))
        StartNewGame((int32)EPlayer::One);
}

const bool UGameStart::TryLoadGame(const FString &SlotName, const int32 PlayerIndex)
{    
    if(UGameplayStatics::DoesSaveGameExist(SlotName, PlayerIndex))
    {
        GameInstance->LoadGame(SlotName, PlayerIndex);
        return true;
    }
    
    return false;
}

void UGameStart::StartNewGame(const int32 PlayerIndex)
{
    AMatch3GameMode* GameMode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GameInstance));
    
    GameMode->SetNewGameState(true);
    GameMode->GetTurnQueue()->CreateFromNames();
    GameInstance->SaveGame(RESET_TO_SLOT, PlayerIndex);
    GameInstance->SaveGame(CONTINUE_GAME_SLOT, PlayerIndex);
}




void UGameQuit::Process()
{
    const bool bIgnorePlatformSpecificRestrictions = true;
    
    UKismetSystemLibrary::QuitGame(GetWorld(),
                                   UGameplayStatics::GetPlayerController(GetWorld(),(int32)EPlayer::One),
                                   EQuitPreference::Quit,
                                   bIgnorePlatformSpecificRestrictions);
}



void UGameRoundEnd::Process()
{
    GlobalEventManager->FinishProcessEvents();
}
