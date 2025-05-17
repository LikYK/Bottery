// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Resource.h"
#include "ResourceKey.h"
#include "ResourceDelegateWrapper.h"
#include "ResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool HasResource(EResourceKey Key);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	UResource* GetResource(EResourceKey Key);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Resources")
	TMap<EResourceKey, UResource*> Resources;
};
