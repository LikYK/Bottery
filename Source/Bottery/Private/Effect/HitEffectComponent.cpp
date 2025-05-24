// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/HitEffectComponent.h"

void UHitEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	Primitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (Primitive)
	{
		Primitive->OnComponentHit.AddUniqueDynamic(this, &UHitEffectComponent::OnHit);
	}
}

void UHitEffectComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the effect is recently applied to this actor
	if (OtherActor == PreviousHitActor)
	{
		return;
	}

	Effect->ApplyEffect(GetOwner(), OtherActor);

	PreviousHitActor = OtherActor;

	GetWorld()->GetTimerManager().SetTimer(
		HitCacheTimerHandle,
		this,
		&UHitEffectComponent::ClearHitCache,
		0.1f,
		false
	);
}

void UHitEffectComponent::ClearHitCache()
{
	PreviousHitActor = nullptr;
}
