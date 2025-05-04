// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriggerEffectComponent.generated.h"


UCLASS(Abstract, ClassGroup=(Effects), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UTriggerEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	void HandleOwnerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	virtual void ApplyEffect(AActor* Target, float EffectMagnitude, int8 Polarity) PURE_VIRTUAL(UMyAbstractComponent::ApplyEffect, );

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float Magnitude = 10;
};
