// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PolarityInterface.h"
#include "Polarity.h"
#include "PolarityDelegateWrapper.h"
#include "ColourComponent.h"
#include "PolarityComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTERY_API UPolarityComponent : public UActorComponent, public IPolarityInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPolarityComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	EPolarity GetPolarity_Implementation() override;

	void SetPolarity_Implementation(EPolarity NewPolarity) override;

	void SwitchPolarity_Implementation() override;

	FLinearColor GetPolarityColour_Implementation(EPolarity TargetPolarity) override;

	virtual UPolarityDelegateWrapper* GetPolarityDelegateWrapper_Implementation() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void SetRandomPolarity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	EPolarity Polarity = EPolarity::Positive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	UColourComponent* ColourComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	FLinearColor PositiveColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	FLinearColor NegativeColour;

	UPROPERTY(BlueprintReadOnly, Category = "Polarity")
	UPolarityDelegateWrapper* PolarityDelegateWrapper;
};
