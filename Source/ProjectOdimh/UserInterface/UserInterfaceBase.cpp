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
    
    CollisionSize = FVector(100.f, 100.f, 100.f);
    
    
    
}

// Called when the game starts or when spawned
void AUserInterfaceBase::BeginPlay()
{
	Super::BeginPlay();


    UICollision->OnInputTouchEnter.AddUniqueDynamic(this, &AUserInterfaceBase::UICommandEnter);
    UICollision->OnInputTouchLeave.AddUniqueDynamic(this, &AUserInterfaceBase::UICommandLeave);
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

void AUserInterfaceBase::SetCollisionSize(const FVector& SetSize)
{

    UICollision->SetBoxExtent(SetSize, true);
    
    // Reset Mesh and Arrow location relative to the collision size
    FVector Location = FVector(0.f, 0.f, 0.f);
    Mesh->SetRelativeLocation(Location);
    Arrow->SetRelativeLocation(Location);
}

void AUserInterfaceBase::UICommandEnter(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp)
{
    UE_LOG(LogTemp, Warning, TEXT("Command Enters... now do something."));
}

void AUserInterfaceBase::UICommandLeave(ETouchIndex::Type Index, UPrimitiveComponent* TouchedComp)
{
    UE_LOG(LogTemp, Warning, TEXT("Command Leaves... now do something."));
}
