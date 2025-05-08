// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PolarityComponent.h"
#include "HasHealth.h"
#include "HealthComponent.h"
#include "HasSpeed.h"
#include "StatComponent.h"
#include "BotteryCharacter.generated.h"

UCLASS(Blueprintable)
class ABotteryCharacter : public ACharacter, public IHasHealth, public IHasSpeed
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

protected:
	// Stat component stores and manages stat values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	UStatComponent* StatComponent;

	// Health
public:
	virtual void TakeDamage_Implementation(float Damage) override;

	virtual float GetCurrentHealth_Implementation() override;

	virtual float GetMaxHealth_Implementation() override;

	virtual UHealthDelegateWrapper* GetHealthDelegateWrapper_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	// Speed
public:
	virtual float GetBaseSpeed_Implementation() override;

	virtual float GetMaxSpeed_Implementation() override;

	virtual float GetMinSpeed_Implementation() override;

	virtual float GetCurrentSpeed_Implementation() override;

	virtual void SetSpeed_Implementation(float NewValue) override;

	virtual void ModifySpeed_Implementation(float ChangeAmount) override;

	virtual UStatDelegateWrapper* GetSpeedDelegateWrapper_Implementation() override;

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
	UFUNCTION(BlueprintCallable, Category = "Polarity")
	EPolarity GetPolarity();

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void SetPolarity(EPolarity NewPolarity);

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void SwitchPolarity();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polarity")
	UPolarityComponent* PolarityComponent;
};

