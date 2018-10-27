// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEvent.generated.h"

class UEventManager;
class UPOdimhGameInstance;

/**
 * A BaseEvent responds to something that just happend in an encapsulated process.
 */
UCLASS(abstract, BlueprintType)
class PROJECTODIMH_API UBaseEvent : public UObject
{
	GENERATED_BODY()
	
public:
    UBaseEvent();
    ~UBaseEvent();
    
    virtual void InitializeEvent();
    
    /** Ensure GetOuter() is not nullptr */
    virtual const bool IsCallerValid();
    
    virtual void Process() {}

    /** Let the state of the event know that it has finished */
    void Finish();
    
    UObject* GetCaller();
    
    const bool IsPendingFinish() const;
    
    UPROPERTY(BlueprintReadOnly)
    UEventManager* GlobalEventManager;

    UPROPERTY(BlueprintReadOnly)
    UPOdimhGameInstance* GameInstance;
    
private:
    uint16 bPendingFinish : 1;
};
