// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flag.h"
#include "ColourComponent.h"
#include "ChangeColourWithFlagComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UChangeColourWithFlagComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChangeColourWithFlagComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Colour Changing")
	void HandleTargetFlagChange(bool bNewTargetValue);

	UFUNCTION(BlueprintCallable, Category = "Colour Changing")
	void ChangeColourWithFlag();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Colour Changing")
	EFlagKey TargetFlagKey;

	UPROPERTY(BlueprintReadOnly, Category = "Colour Changing")
	UFlag* TargetFlag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Colour Changing")
	UColourComponent* ColourComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Changing")
	FLinearColor TrueColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour Changing")
	FLinearColor FalseColour;
};
