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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UResourceComponent* ResourceComponent;

	// Stat component stores and manages stat values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Polarity")
	UFlagComponent* FlagComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashVelocity = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashCooldown = 1.0f;

private:
	bool bCanDash = true;
	FTimerHandle DashCooldownTimer;
};

