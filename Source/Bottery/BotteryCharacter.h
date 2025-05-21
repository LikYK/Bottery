// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ResourceComponent.h"
#include "StatComponent.h"
#include "FlagComponent.h"
#include "BotteryCharacter.generated.h"

UCLASS(Blueprintable)
class ABotteryCharacter : public ACharacter//, public IHasHealth, public IHasStats, public IHasPolarity
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

public:
	UFUNCTION(BlueprintCallable, Category = "Dash")
	void Dash();

	UFUNCTION(BlueprintCallable, Category = "Polarity")
	void ChangePolarity();

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool UseStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Magnitude")
	void HandleMagnitudeChange(float CurrentValue, float BaseValue);

	UFUNCTION(BlueprintCallable, Category = "Speed")
	void HandleSpeedChange(float CurrentValue, float BaseValue);

protected:
	UPROPERTY()
	UResourceComponent* ResourceComponent;

	UPROPERTY()
	UStatComponent* StatComponent;

	UPROPERTY()
	UFlagComponent* FlagComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	UAnimMontage* DashMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DashSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ChangePolaritySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashVelocity = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float DashStamina = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float ChangePolarityStamina = 20.0f;

private:
	bool bCanDash = true;
	FTimerHandle DashCooldownTimer;
};

