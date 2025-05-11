// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceEffectComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UBounceEffectComponent::UBounceEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBounceEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (auto* PM = GetOwner()->FindComponentByClass<UProjectileMovementComponent>())
	{
		PM->OnProjectileBounce.AddUniqueDynamic(this, &UBounceEffectComponent::HandleProjectileBounce);
	}
}

void UBounceEffectComponent::HandleProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("bounce handler")));
	AActor* OtherActor = ImpactResult.GetActor();

	if (!EffectInstance)
	{
		CreateEffectInstance();
	}

	EffectInstance->ApplyEffect(GetOwner(), OtherActor);
}

