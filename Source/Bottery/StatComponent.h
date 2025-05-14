// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatInterface.h"
#include "StatKey.h"
#include "Stat.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UStatComponent : public UActorComponent, public IStatInterface
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
	bool HasStat_Implementation(EStatKey Key) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStatBase_Implementation(EStatKey Key) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStatMax_Implementation(EStatKey Key) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStatMin_Implementation(EStatKey Key) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStatValue_Implementation(EStatKey Key) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetStatValue_Implementation(EStatKey Key, float NewSpeed) override;

	// Increases or decreases speed by a fixed amount for Steps times.
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyStat_Implementation(EStatKey Key, float ChangeAmount) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	UStatDelegateWrapper* GetStatDelegateWrapper_Implementation(EStatKey Key) override;

	//UFUNCTION(BlueprintCallable, Category = "Stats")
	//UStat* GetStat(EStatKey StatKey);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	TMap<EStatKey, UStat*> Stats;
};
