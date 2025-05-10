// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HasHealth.h"
#include "HealthComponent.h"
#include "HasStats.h"
#include "StatComponent.h"
#include "HasPolarity.h"
#include "PolarityComponent.h"
#include "BotteryCharacter.generated.h"

UCLASS(Blueprintable)
class ABotteryCharacter : public ACharacter, public IHasHealth, public IHasStats, public IHasPolarity
{
	GENERATED_BODY()

public:
	ABotteryCharacter(const FObjectInitializer& ObjectInitializer);

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Health
public:
	virtual void TakeDamage_Implementation(float Damage) override;

	virtual float GetCurrentHealth_Implementation() override;

	virtual float GetMaxHealth_Implementation() override;

	virtual UHealthDelegateWrapper* GetHealthDelegateWrapper_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	// Stats (Speed, Magnitude)
public:
	virtual bool HasStat_Implementation(EStatKey Key) override;

	virtual float GetStatBase_Implementation(EStatKey Key) override;

	virtual float GetStatMax_Implementation(EStatKey Key) override;

	virtual float GetStatMin_Implementation(EStatKey Key) override;

	virtual float GetStatValue_Implementation(EStatKey Key) override;

	virtual void SetStatValue_Implementation(EStatKey Key, float NewValue) override;

	virtual void ModifyStat_Implementation(EStatKey Key, float ChangeAmount) override;

	virtual UStatDelegateWrapper* GetStatDelegateWrapper_Implementation(EStatKey Key) override;

protected:
	// Stat component stores and manages stat values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UStatComponent* StatComponent;

	// Speed
public:
	//virtual float GetBaseSpeed_Implementation() override;

	//virtual float GetMaxSpeed_Implementation() override;

	//virtual float GetMinSpeed_Implementation() override;

	//virtual float GetCurrentSpeed_Implementation() override;

	//virtual void SetSpeed_Implementation(float NewValue) override;

	//virtual void ModifySpeed_Implementation(float ChangeAmount) override;

	//virtual UStatDelegateWrapper* GetSpeedDelegateWrapper_Implementation() override;

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	//UCharacterMovementComponent* MovementComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed")
	//USpeedComponent* SpeedComponent;

	// Speed component accepts a function as OnSpeedChanged handler
	// This is an effort to decouple speed component from actor movement components (character movement, projectile movement etc.)
	//UFUNCTION(BlueprintCallable, Category = "Speed")
	//void SetSpeed(float NewSpeedMultiplier, float NewSpeed);

	// Polarity
public:
	virtual EPolarity GetPolarity_Implementation() override;

	virtual void SetPolarity_Implementation(EPolarity NewPolarity) override;

	virtual void SwitchPolarity_Implementation() override;

	virtual FLinearColor GetPolarityColour_Implementation() override;

	virtual UPolarityDelegateWrapper* GetPolarityDelegateWrapper_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Polarity")
	UPolarityComponent* PolarityComponent;

//public:
//	UFUNCTION(BlueprintCallable, Category = "Polarity")
//	EPolarity GetPolarity();
//
//	UFUNCTION(BlueprintCallable, Category = "Polarity")
//	void SetPolarity(EPolarity NewPolarity);
//
//	UFUNCTION(BlueprintCallable, Category = "Polarity")
//	void SwitchPolarity();
//
//protected:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
//	UPolarityComponent* PolarityComponent;
};

