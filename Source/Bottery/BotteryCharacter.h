// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "PolarityComponent.h"
#include "HasHealth.h"
#include "UObject/ScriptDelegateFwd.h"
#include "BotteryCharacter.generated.h"

UCLASS(Blueprintable)
class ABotteryCharacter : public ACharacter, public IHasHealth
{
	GENERATED_BODY()

public:
	ABotteryCharacter();

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

	virtual UHealthDelegatesWrapper* GetHealthDelegates_Implementation() override;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//UHealthDelegatesWrapper* HealthDelegates;

	//UPROPERTY(BlueprintAssignable, Category = "Health")
	//FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UHealthComponent* HealthComponent;

//private:
//	UFUNCTION(BlueprintCallable, Category = "Health")
//	void BroadcastHealthChangedInternal(float CurrentHealth, float MaxHealth);

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

