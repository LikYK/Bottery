// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbMovementComponent.h"
#include "ActorData/ResourceComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "Components/TimelineComponent.h"
#include "Orb.generated.h"

UCLASS()
class BOTTERY_API AOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void HandleFadeProgress(float Value);

	UFUNCTION()
	virtual void HandleFadeInFinished();

	UFUNCTION()
	virtual void HandleFadeOutFinished();

	UFUNCTION()
	virtual void HandleBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	UFUNCTION()
	virtual void HandleOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32               OtherBodyIndex,
		bool                bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void HandleHealthDepleted();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UOrbMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UResourceComponent* ResourceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UTimelineComponent* FadeTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* OverlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* EffectSoundAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UCurveFloat* FadeInCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UCurveFloat* FadeOutCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraSystem* FXOverlap;

	UPROPERTY(BlueprintReadOnly, Category = "VFX")
	UMaterialInstanceDynamic* DynamicMaterial;
};
