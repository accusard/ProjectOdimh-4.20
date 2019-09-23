// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridControlComponent.generated.h"

class ATile;
class USoundCue;
class AGrid;

/**
 * Allow actors the functionality to manipulate the grid
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UGridControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridControlComponent();
    
    ATile* GetLastGrab();
    ATile* GrabTile(const FHitResult& Hit, AActor* Controller);
    
    const bool IsTilePicked() const;
    void SetDeltaDirection(const float Dir);
    const float GetDeltaDirection() const;
    
protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* GrabCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* ReleaseCue;

private:
    ATile* TileLastGrab;
    bool bPickedTile : 1;
    float DeltaDirection;
};
