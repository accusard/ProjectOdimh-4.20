// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameTypes.h"
#include "ClassInterface/TileHandlingInterface.h"
#include "GridController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API AGridController : public AController, public ITileHandlingInterface
{
	GENERATED_BODY()
	
public:
    AGridController();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintPure)
    virtual class UTileHandlerComponent* GetTileHandler() override;
    
    virtual void NotifyPick(ATile* Tile) override;
    
    void MoveTile(class ATile* Tile, const EDirection& Dir, const float Delta);
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UTileHandlerComponent* TileHandlerComponent;
};
