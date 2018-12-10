// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "UserInterfaceBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
AUserInterfaceBase::AUserInterfaceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
    UICollision = CreateDefaultSubobject<UBoxComponent>(FName("UI Collision"));
    Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
    RootComponent = UICollision;
    
    CollisionSize = FVector(200.f, 32.f, 32.f);
    
    
    
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

void AUserInterfaceBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    SetCollisionSize(CollisionSize);
}

void AUserInterfaceBase::SetCollisionSize(const FVector& Size)
{
    UICollision->SetBoxExtent(Size, true);
    
    // update Mesh and arrow location relative to the collision size
    FVector Location = FVector(-Size.X, 0.f, 0.f);
    Mesh->SetRelativeLocation(Location);
    
    Arrow->SetRelativeLocation(Location);
}
