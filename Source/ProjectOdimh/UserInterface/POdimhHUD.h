// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "POdimhHUD.generated.h"

class UPOdimhWidget;

//TODO: need class description
/**
 * A HUD
 */
UCLASS()
class PROJECTODIMH_API APOdimhHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    // TODO: widget is created in blueprint.. make an event to get its reference?
    /** Setup function to create player 1's widget from blueprint */
    UPOdimhWidget* CreateWidgetFromBlueprint(TSubclassOf<UPOdimhWidget> WidgetBlueprint);
    
    /** Set the current active widget so that the HUD can have access to it */
    void SetActiveWidget(UUserWidget* Widget);
    
    /** Get the currently active widget */
    UFUNCTION(BlueprintCallable)
    UPOdimhWidget* GetMenuSelectionWidget();
    
protected:
    void BeginPlay() override;
    
    /** Set blueprint for the main menu UI */
    UPROPERTY(EditDefaultsOnly, Category="Widget")
    TSubclassOf<UPOdimhWidget> MenuBlueprint;
    UPOdimhWidget* MenuSelection;
    
    /** The pointer to the currently active widget */
    UUserWidget* ActiveWidget;
};
