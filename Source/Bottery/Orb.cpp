// Fill out your copyright notice in the Description page of Project Settings.


#include "Orb.h"
#include <Kismet/GameplayStatics.h>

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
	
	if (auto* PM = FindComponentByClass<UProjectileMovementComponent>())
	{
		PM->OnProjectileBounce.AddUniqueDynamic(this, &AOrb::HandleBounce);
	}

	if (auto* Primitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Primitive->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOrb::HandleOverlap);
	}
}

// Called every frame
void AOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrb::HandleBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (BounceSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			BounceSound,
			GetActorLocation(),
			1.0f,
			1.0f,
			0.0f,
			EffectSoundAttenuation
		);
	}
}

void AOrb::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			OverlapSound,
			GetActorLocation(),
			1.0f,
			1.0f,
			0.0f,
			nullptr
		);
	}

	// Destroy self next frame, to ensure overlap handlers from other sources (eg. OverlapEffectComponent) can fire
	GetWorldTimerManager().SetTimerForNextTick(
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				if (IsValid(this))
				{
					Destroy();
				}
			})
	);
}

