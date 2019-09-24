// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileHandlerComponent.generated.h"

class ATile;
class USoundCue;
class AGrid;

/**
 * Allow actors the functionality to manipulate the grid
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UTileHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

    friend class ITileHandlingInterface;
    friend class AGrid;
public:	
	// Sets default values for this component's properties
	UTileHandlerComponent();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    void SetPlayerControlled(const bool bPlayerControlled = true);
    const bool TileIsPlayerControlled() const;
    
    void SetDeltaDirection(const float Dir);
    const float GetDeltaDirection() const;
    
    void NotifyController(AActor* Controller, ATile* TilePicked);
    void NotifyReleasePickedTile();
    
protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* GrabCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* ReleaseCue;

private:
    ATile* TileLastGrab;
    ATile* TilePicked;
    float DeltaDirection;
    bool bTileIsPlayerControlled : 1;
};
