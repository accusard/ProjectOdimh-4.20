// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Game/Queue.h"
#include "PendingKillQueue.generated.h"


const float INIT_KILL_INTERVALS = 30.f; // default should be 30.f

/**
 * DEPRECATED
 *  A queue that periodically "cleans" itself by MarkPendingKill() on all objects in the queue list at a specified interval.
 */
UCLASS()
class PROJECTODIMH_API APendingKillQueue : public AQueue
{
	GENERATED_BODY()
	
public:
    APendingKillQueue();
    
    virtual void Tick(float DeltaTime) override;
    
    /** Explicitly mark all objects in the list to be killed */
    void KillList();
    
    void SetKillInterval(const float Seconds);

    
private:

	
};
