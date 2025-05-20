// Fill out your copyright notice in the Description page of Project Settings.


#include "Orb.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ScaleSizeWithStatComponent.h"
#include "Components/TimelineComponent.h"

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

	FadeInTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeInTimeline"));
}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
	// Create a dynamic material to change opacity
	UMeshComponent* Mesh = FindComponentByClass<UMeshComponent>();
	UMaterialInterface* Mat = Mesh->GetMaterial(0);

	DynamicMaterial = Cast<UMaterialInstanceDynamic>(Mat);
	if (!DynamicMaterial)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Mat, this);

		Mesh->SetMaterial(0, DynamicMaterial);
	}
	DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 0.0f);
	
	// Disable collision
	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetRootComponent());
	Primitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Stop movements
	MovementComponent->Deactivate();

	// Update opacity with timeline
	FOnTimelineFloat ProgressCallback;
	ProgressCallback.BindUFunction(this, FName(TEXT("HandleFadeInProgress")));
	FadeInTimeline->AddInterpFloat(FadeInCurve, ProgressCallback);

	// Enable collision and movement after timeline is finished
	FOnTimelineEvent FinishedCallback;
	FinishedCallback.BindUFunction(this, FName(TEXT("HandleFadeInFinished")));
	FadeInTimeline->SetTimelineFinishedFunc(FinishedCallback);

	// Start timeline to fade in from opacity 0 to 1
	FadeInTimeline->SetLooping(false);
	FadeInTimeline->PlayFromStart();
}

// Called every frame
void AOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrb::HandleFadeInProgress(float Value)
{
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Spawning Orb, value:%f"), Value));
	DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), Value);
}

void AOrb::HandleFadeInFinished()
{
	MovementComponent->Activate();
	// Call Init() again to give the orb its base velocity, since the velocity was set to zero when deactivating in BeginPlay()
	MovementComponent->Init();
	MovementComponent->OnProjectileBounce.AddUniqueDynamic(this, &AOrb::HandleBounce);

	if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Primitive->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOrb::HandleOverlap);
		Primitive->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
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

	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXOverlap, GetActorLocation(), FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, false, ENCPoolMethod::None, true);
	if (NiagaraComp)
	{
		float OrbScale = 1.0f;
		if (UScaleSizeWithStatComponent* ScaleComp = GetComponentByClass<UScaleSizeWithStatComponent>())
		{
			OrbScale = ScaleComp->GetScale();
		}

		NiagaraComp->SetNiagaraVariableFloat(TEXT("Scale"), OrbScale);
		NiagaraComp->Activate();
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

