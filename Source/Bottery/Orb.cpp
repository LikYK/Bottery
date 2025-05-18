// Fill out your copyright notice in the Description page of Project Settings.


#include "Orb.h"

// Sets default values
AOrb::AOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UOrbMovementComponent>(TEXT("Movement"));
	MovementComponent->bShouldBounce = true;
	MovementComponent->Bounciness = 1.0f;
	MovementComponent->Friction = 0.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->bConstrainToPlane = true;
	MovementComponent->bSnapToPlaneAtStart = true;
	MovementComponent->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
	MovementComponent->SetPlaneConstraintOrigin(FVector(0.0f, 0.0f, 100.f));
}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

