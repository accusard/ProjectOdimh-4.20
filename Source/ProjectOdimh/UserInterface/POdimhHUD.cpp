// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "POdimhHUD.h"
#include "Gametypes.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/POdimhWidget.h"

UPOdimhWidget* APOdimhHUD::CreateWidgetFromBlueprint(TSubclassOf<UPOdimhWidget> WidgetBlueprint)
{
    UPOdimhWidget* WidgetPtr = nullptr;
    
    // if widget blueprint exists
    if(WidgetBlueprint)
    {
        APlayerController* Player = UGameplayStatics::GetPlayerController(GetWorld(), (uint8)EPlayer::One);
        WidgetPtr = CreateWidget<UPOdimhWidget>(Player, WidgetBlueprint);
    }
    
    return WidgetPtr;
}

void APOdimhHUD::SetActiveWidget(UUserWidget* Widget)
{
    if(Widget)
    {
        ActiveWidget = Widget;
        ActiveWidget->AddToViewport();
    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("No active blueprint available to create widget!"));
    }
}

UPOdimhWidget* APOdimhHUD::GetMenuSelectionWidget()
{
    return MenuSelection;
}

void APOdimhHUD::BeginPlay()
{
    Super::BeginPlay();
}
