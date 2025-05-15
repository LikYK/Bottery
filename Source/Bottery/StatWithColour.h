// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "StatWithColour.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UStatWithColour : public UStat
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "StatColour")
	FLinearColor GetStatColour();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatColour")
	FLinearColor Colour;
};
