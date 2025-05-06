// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PolarityComponent.generated.h"

UENUM(BlueprintType)
enum class EPolarity : uint8
{
	Negative UMETA(DisplayName = "Negative"),
	Positive UMETA(DisplayName = "Positive"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPolarityChangedSignature, EPolarity, Polarity, FLinearColor, Color);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOTTERY_API UPolarityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPolarityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Polarity")
	EPolarity GetPolarity();

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void SetPolarity(EPolarity NewPolarity);

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void SwitchPolarity();

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	FLinearColor GetPolarityColor();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnPolarityChangedSignature OnPolarityChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	EPolarity Polarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	FLinearColor PositiveColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	FLinearColor NegativeColor;
};
