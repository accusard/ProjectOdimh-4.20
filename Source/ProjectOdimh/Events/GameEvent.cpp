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
    AMatch3GameMode* GameMode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GameInstance));
    
    GameMode->SetNewGameState(true);
    GameMode->GetTurnQueue()->CreateFromNames();
    GameInstance->SaveGame(RESET_TO_SLOT);
    GameInstance->SaveGame(CONTINUE_GAME_SLOT);
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
