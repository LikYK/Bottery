// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionEffectComponent.h"
#include "OverlapEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UOverlapEffectComponent : public UCollisionEffectComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOverlapEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32               OtherBodyIndex,
		bool                bFromSweep,
		const FHitResult& SweepResult
	);
};
