// Fill out your copyright notice in the Description page of Project Settings.


#include "Orb/Orb.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Component/ScaleSizeWithStatComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AOrb::AOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Avoid spawning inside other actors
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

	FadeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeTimeline"));
}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
	// Check if there is a resource component and cache it if found (to access health resource if there is one)
	ResourceComponent = GetComponentByClass<UResourceComponent>();

	// Create a dynamic material to change opacity
	UMeshComponent* Mesh = FindComponentByClass<UMeshComponent>();
	UMaterialInterface* Mat = Mesh->GetMaterial(0);

	// If material on mesh is not dynamic instance, create a dynamic instance of it and replace the current one
	// This enables runtime parameter changes in the material (like colour, opacity)
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

	// Stop health decay if there is a health resource
	if (ResourceComponent && ResourceComponent->HasResource(EResourceKey::Health))
	{
		ResourceComponent->GetResource(EResourceKey::Health)->SetDecay(false);
	}

	// Update opacity with timeline (FadeInCurve goes from 0 to 1)
	FOnTimelineFloat ProgressCallback;
	ProgressCallback.BindUFunction(this, FName(TEXT("HandleFadeProgress")));
	FadeTimeline->AddInterpFloat(FadeInCurve, ProgressCallback, NAME_None, FName(TEXT("Fade")));

	// Call function to enable collision, health decay and movement after timeline is finished
	FOnTimelineEvent FinishedCallback;
	FinishedCallback.BindUFunction(this, FName(TEXT("HandleFadeInFinished")));
	FadeTimeline->SetTimelineFinishedFunc(FinishedCallback);

	// Start timeline to fade in from opacity 0 to 1
	FadeTimeline->SetLooping(false);
	FadeTimeline->PlayFromStart();
}

// Called every frame
void AOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrb::HandleFadeProgress(float Value)
{
	DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), Value);
}

void AOrb::HandleFadeInFinished()
{
	// If there is a health resource, start health decay and bind handler to handle health depleted
	if (ResourceComponent && ResourceComponent->HasResource(EResourceKey::Health))
	{
		UResource* Health = ResourceComponent->GetResource(EResourceKey::Health);

		// Randomize health decay rate between min and max for a random lifespan
		UStat* HealthDecay = Health->GetDecayRateStat();
		HealthDecay->SetValue(FMath::RandRange(HealthDecay->GetMinValue(), HealthDecay->GetMaxValue()));

		Health->OnResourceDepleted.AddUniqueDynamic(this, &AOrb::HandleHealthDepleted);
		Health->SetDecay(true);
	}

	// Start movement and bind bounce handler
	MovementComponent->Activate();
	// Call Init() again to give the orb its base velocity, since the velocity was set to zero when deactivating in BeginPlay()
	MovementComponent->Init();
	MovementComponent->OnProjectileBounce.AddUniqueDynamic(this, &AOrb::HandleBounce);

	// Enable collision and bind overlap handler
	if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Primitive->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOrb::HandleOverlap);
		Primitive->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AOrb::HandleFadeOutFinished()
{
	Destroy();
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

	// Spawn a particle system
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

void AOrb::HandleHealthDepleted()
{
	// Replace the FadeInCurve from BeginPlay with a FadeOutCurve, 
	// which goes from 1 to 0 and have a longer duration (fades slower)
	FadeTimeline->SetFloatCurve(FadeOutCurve, FName(TEXT("Fade")));

	// Replace the function to invoke after the timeline(fading) is finished to self-destrcut
	FOnTimelineEvent FinishedCallback;
	FinishedCallback.BindUFunction(this, FName(TEXT("HandleFadeOutFinished")));
	FadeTimeline->SetTimelineFinishedFunc(FinishedCallback);

	FadeTimeline->PlayFromStart();
}