// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Events/BaseEvent.h"
#include "GameEvent.generated.h"



/**
 *
 */
UCLASS()
class PROJECTODIMH_API UGameEvent : public UBaseEvent
{
	GENERATED_BODY()
	
public:
    virtual void InitializeEvent() override;
    

    

};



/**
 * Begin the process of starting a game. This only happen during level blueprint event start.
 */
UCLASS()
class PROJECTODIMH_API UGameStart : public UGameEvent
{
    GENERATED_BODY()
    
public:
    virtual void InitializeEvent() override;
    virtual void Process() override;
    
    
    
private:
    const bool TryLoadGame();
    void StartNewGame();
    

};



/**
 *
 */
UCLASS()
class PROJECTODIMH_API UGameQuit : public UGameEvent
{
    GENERATED_BODY()
    
public:
    virtual void Process() override;
    
private:
    
};



UCLASS()
class PROJECTODIMH_API UGameRoundEnd : public UGameEvent
{
    GENERATED_BODY()
    
public:
    virtual void Process() override;
};

