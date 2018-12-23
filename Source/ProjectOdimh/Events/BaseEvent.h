// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEvent.generated.h"

class UEventManager;
class UPOdimhGameInstance;

/**
 * A UBaseEvent class is a wrapper class that responds to an event that just happend in an encapsulated process.
 */
UCLASS(abstract, BlueprintType)
class PROJECTODIMH_API UBaseEvent : public UObject
{
	GENERATED_BODY()
	
public:
    UBaseEvent();
    ~UBaseEvent();
    
    virtual void InitializeEvent();
    
    /** Ensure GetOuter() is not nullptr in derived classes. Will always return false if parent class gets called*/
    virtual const bool IsCallerValid();
    
    void Start();
    
    virtual void OnEventStart() {}
    virtual void OnEventEnd() {}

    /** Let the state of the event know that it has finished */
    void Finish();
    
    /** The caller of the event is the outer class that created this event */
    UObject* GetCaller();
    
    /** Checks if Finish have not been called yet */
    const bool IsPendingFinish() const;
    
    UPROPERTY(BlueprintReadOnly)
    UEventManager* GlobalEventManager;

    UPROPERTY(BlueprintReadOnly)
    UPOdimhGameInstance* GameInstance;
    
private:
    uint16 bPendingFinish : 1;

};
