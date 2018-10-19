// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAbility;

/**
 * Give an entity capabilities
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTODIMH_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

    /** Try to destroy this object by using an ability */
    const bool TryDestroy(UAbility* Ability);
                    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    /** Determines if this entity can be destroyed by another entity */
    UPROPERTY(EditAnywhere, Category="Abilities")
    bool bIndestructible;
	
};
