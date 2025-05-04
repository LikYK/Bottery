// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "BotteryCharacter.generated.h"

UCLASS(Blueprintable)
class ABotteryCharacter : public ACharacter
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

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(int32 Damage);

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthBarFill();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedSignature OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	UHealthComponent* HealthComponent;

private:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void BroadcastHealthChangedInternal(int32 CurrentHealth, int32 MaxHealth, float Fill);
};

