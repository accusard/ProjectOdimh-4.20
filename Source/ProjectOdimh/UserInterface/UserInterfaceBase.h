// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserInterfaceBase.generated.h"

UCLASS()
class PROJECTODIMH_API AUserInterfaceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserInterfaceBase();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    
    void SetCollisionSize(const FVector& Size);
    
    
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Mesh;
    UPROPERTY()
    class UBoxComponent* UICollision;
    UPROPERTY()
    class UArrowComponent* Arrow;

private:
    UPROPERTY(EditAnywhere, Category="Collision")
    FVector CollisionSize;
	
};
