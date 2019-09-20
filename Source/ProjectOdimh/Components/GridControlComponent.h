// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridControlComponent.generated.h"

class ATile;
class USoundCue;

/**
 * Allow actors to have control over the grid
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UGridControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridControlComponent();
    
    ATile* GetLastGrab();
    ATile* GrabTile(const FHitResult& Hit);
    
protected:
    UFUNCTION(BlueprintImplementableEvent)
    void PickTile(const FVector& Location);
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* GrabCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* ReleaseCue;

private:
    ATile* TileLastGrab;
	
};
