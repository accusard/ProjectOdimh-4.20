// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhGameInstance.h"
#include "POdimhSaveGame.h"
#include "EngineUtils.h"
#include "Gametypes.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Events/EventManager.h"
#include "Events/BaseEvent.h"



UPOdimhGameInstance::UPOdimhGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    
}

void UPOdimhGameInstance::Init()
{
    Super::Init();
    GlobalEvent = NewObject<UEventManager>();
}

UPOdimhSaveGame* UPOdimhGameInstance::CreateSaveGameObject()
{
    return Cast<UPOdimhSaveGame>(UGameplayStatics::CreateSaveGameObject(UPOdimhSaveGame::StaticClass()));
}

void UPOdimhGameInstance::SaveGameToSlot(USaveGame* Data, const FString& SlotName, const int32 Player)
{
    UGameplayStatics::SaveGameToSlot(Data, SlotName, Player);
}

UPOdimhSaveGame* UPOdimhGameInstance::LoadGameFromSlot(const FString& SlotName, const int32 Player)
{
    UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, Player));
    
    Data->SaveSlotName = SlotName;
    Data->UserIndex = Player;
    
    return Data;
}

const bool UPOdimhGameInstance::DoesSaveGameExist(const FString& SlotName, const int32 UserIndex)
{
    return UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex);
}


void UPOdimhGameInstance::ResetGame()
{
    LoadGame(RESET_TO_SLOT);
    SaveGame(CONTINUE_GAME_SLOT);
}

void UPOdimhGameInstance::SaveGame(const FString& SlotName)
{
    UPOdimhSaveGame* Data = CreateSaveGameObject();
    Data->SaveSlotName = SlotName;
    
    for(TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(IDataSaveInterface* ActorSaveInterface = Cast<IDataSaveInterface>(*ActorItr))
        {
            ActorSaveInterface->Save(Data);
            UGameplayStatics::SaveGameToSlot(Data, Data->SaveSlotName, (int32)EPlayer::One);
        }
    }
}

void UPOdimhGameInstance::LoadGame(const FString& SlotName)
{
    if(!DoesSaveGameExist(SlotName, (int32)EPlayer::One))
        return;
    
    // init a new save game object
    UPOdimhSaveGame* Data = CreateSaveGameObject();
    
    // load game from slot
    Data = LoadGameFromSlot(SlotName, (int32)EPlayer::One);
    
    for(TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        LoadActor(*ActorItr, Data);
        LoadComponents(*ActorItr, Data);
     }
}

void UPOdimhGameInstance::LoadActor(AActor* Actor, USaveGame* Data)
{
    if(IDataSaveInterface* ActorSaveInterface = Cast<IDataSaveInterface>(Actor))
    {
        if(ActorSaveInterface->Load(Data))
        {
            UE_LOG(LogTemp, Warning, TEXT("LoadActor: %s data loaded successfully.."), *ActorSaveInterface->_getUObject()->GetName());
        }
    }
}

void UPOdimhGameInstance::LoadComponents(AActor* Actor, USaveGame* Data)
{
    TInlineComponentArray<UActorComponent*> Components;
    Actor->GetComponents(Components);
    
    for(UActorComponent* Comp : Components)
    {
        if(IDataSaveInterface* LoadingInterface = Cast<IDataSaveInterface>(Comp))
        {
            if(LoadingInterface->Load(Data))
            {
                UE_LOG(LogTemp, Warning, TEXT("LoadComponent: %s data loaded successfully.."), *LoadingInterface->_getUObject()->GetName());
            }
        }
    }
}

