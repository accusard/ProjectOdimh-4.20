// Copyright 2017-2019 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TileHandlingInterface.generated.h"

class UActorPickHandlerComponent;
class ATile;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTileHandlingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PROJECTODIMH_API ITileHandlingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual UActorPickHandlerComponent* GetTileHandler() = 0;
    virtual void NotifyPick(AActor* Actor, UActorPickHandlerComponent* PickHandler) = 0;
    
    AActor* GetLastGrab(UActorPickHandlerComponent* Comp);
    AActor* GetTilePicked(UActorPickHandlerComponent* Comp);
    AActor* GrabTile(AActor* Controller, const FHitResult& Hit, UActorPickHandlerComponent* Comp);
    const bool IsTilePicked(UActorPickHandlerComponent* Comp);
    
protected:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actor Pick Interface")
    void OnReleaseTile(UActorPickHandlerComponent* TileHandlerComp);
    void OnReleaseTile_Implementation(UActorPickHandlerComponent* TileHandlerComp);
    
    UFUNCTION(BlueprintImplementableEvent, Category="Actor Pick Interface")
    void OnPickTile(const FVector& Location);
};
