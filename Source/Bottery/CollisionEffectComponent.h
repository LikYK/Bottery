// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Effect.h"
#include "CollisionEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UCollisionEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//UFUNCTION()
	//virtual void CreateEffectInstance();

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	//TSubclassOf<UEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Effect")
	UEffect* Effect;
};
