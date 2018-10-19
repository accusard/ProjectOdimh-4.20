// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Powerup.h"

#if !UE_BUILD_SHIPPING
#include "Engine.h"
#include "POdimhGameInstance.h"
#endif

// Sets default values
APowerup::APowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APowerup::Activate(AActor* Target)
{
#if !UE_BUILD_SHIPPING
    FString Message = FString::Printf(TEXT("APowerup::Activate() have not been implemented yet."));
    Cast<UPOdimhGameInstance>(GetGameInstance())->DebugInfo->PrintToScreen(Message);
#endif
}


void APowerup::Deactivate(AActor* Target)
{
#if !UE_BUILD_SHIPPING
    FString Message = FString::Printf(TEXT("APowerup::Deactivate() have not been implemented yet."));
    Cast<UPOdimhGameInstance>(GetGameInstance())->DebugInfo->PrintToScreen(Message);
#endif
}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

