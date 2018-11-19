// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "GameEvent.h"
#include "POdimhGameInstance.h"
#include "Events/EventManager.h"
#include "Entities/Game/TurnEntity.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Game/PendingKillQueue.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Gametypes.h"
#if !UE_BUILD_SHIPPING
#include "Entities/Game/Queue.h"
#endif




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
    if(!TryLoadGame())
        StartNewGame();
}

const bool UGameStart::TryLoadGame()
{    
    if(GameInstance->DoesSaveGameExist(CONTINUE_GAME_SLOT, (int32)EPlayer::One))
    {
        GameInstance->LoadGame(CONTINUE_GAME_SLOT);
        return true;
    }
    
    return false;
}

void UGameStart::StartNewGame()
{
    GameInstance->SaveGame(RESET_TO_SLOT);
    GameInstance->SaveGame(CONTINUE_GAME_SLOT);
    AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GameInstance);
    UE_LOG
}




void UGameQuit::Process()
{

    UKismetSystemLibrary::QuitGame(GetWorld(),
                                   UGameplayStatics::GetPlayerController(GetWorld(),
                                                                         (uint)EPlayer::One), EQuitPreference::Quit);
}



void UGameRoundEnd::Process()
{
    GlobalEventManager->FinishProcessEvents();
}
