// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameTypes.h"
#include "ClassInterface/PickHandlerInterface.h"
#include "GridController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTODIMH_API AGridController : public AController, public IPickHandlerInterface
{
	GENERATED_BODY()
	
public:
    AGridController();
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintPure)
    virtual class UActorPickHandlerComponent* GetPickHandler() override;
    
    UFUNCTION()
    virtual void BeginAIPick(APawn* PossessPawn);
    
    UFUNCTION()
    virtual void HandlePick(AActor* PickedTile);
    
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UActorPickHandlerComponent* TileHandlerComponent;
};
