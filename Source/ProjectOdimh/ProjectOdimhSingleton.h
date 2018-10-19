// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectOdimhSingleton.generated.h"

class AEventManager;


/**
 * DEPRECATED
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTODIMH_API UProjectOdimhSingleton : public UObject
{
	GENERATED_BODY()
	
public:
    UProjectOdimhSingleton(const FObjectInitializer& ObjectInitializer);
    

	
};
