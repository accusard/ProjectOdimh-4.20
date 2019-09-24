// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Events/BaseEvent.h"
#include "PlayerInputEvent.generated.h"





class AGrid;

USTRUCT(BlueprintType)
struct FInputData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(BlueprintReadOnly)
    int InputIndex;
    
    UPROPERTY(BlueprintReadOnly)
    FVector Location;
    
    
};

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTODIMH_API UPlayerInputEvent : public UBaseEvent
{
	GENERATED_BODY()
	
public:
    virtual void OnEventStart() override;
    virtual void OnEventEnd() override;
    
    void RegisterInput(ETouchIndex::Type FingerIndex, const FVector& Location);
    
protected:
    UPROPERTY(BlueprintReadOnly)
    FInputData TouchData;
   
    
private:
    void NotifyTileTouch(AGrid* Grid, AActor* TouchedActor);
    void NotifyRelease(AGrid* Grid);

};
