// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/CollisionEffectComponent.h"
#include "HitEffectComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BOTTERY_API UHitEffectComponent : public UCollisionEffectComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector         NormalImpulse,
		const FHitResult& Hit
	);

	UFUNCTION()
	void ClearHitCache();

	// Unreal's OnComponentHit can fire multiple times in the same frame,
	// store the previously hit actor to compare in OnHit() so effect is not triggered multiple times in a single hit
	UPROPERTY()
	AActor* PreviousHitActor;

	UPROPERTY()
	UPrimitiveComponent* Primitive;

	FTimerHandle HitCacheTimerHandle;
};
