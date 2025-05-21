// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stat.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool HasStat(EStatKey Key);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStat* GetStat(EStatKey Key);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	TMap<EStatKey, UStat*> Stats;
};
