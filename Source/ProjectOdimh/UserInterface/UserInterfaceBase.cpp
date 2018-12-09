// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "UserInterfaceBase.h"


// Sets default values
AUserInterfaceBase::AUserInterfaceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUserInterfaceBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUserInterfaceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

