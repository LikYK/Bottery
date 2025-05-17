// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flag.h"
#include "FlagKey.h"
#include "FlagDelegateWrapper.h"
#include "FlagComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UFlagComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlagComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Flags")
	bool HasFlag(EFlagKey Key);

	UFUNCTION(BlueprintCallable, Category = "Flags")
	UFlag* GetFlag(EFlagKey Key);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Flags")
	TMap<EFlagKey, UFlag*> Flags;
};
