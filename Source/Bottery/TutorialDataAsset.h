// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TutorialDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FTutorialPage
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UTexture2D* Image;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Text;
};

UCLASS(BlueprintType)
class BOTTERY_API UTutorialDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName Identifier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Title;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<FTutorialPage> Pages;
};
