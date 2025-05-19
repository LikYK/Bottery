// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionEffectComponent.h"

// Sets default values for this component's properties
UCollisionEffectComponent::UCollisionEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollisionEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UCollisionEffectComponent::PlayEffectSound()
//{
//	if (!EffectSound)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UCollisionEffectComponent::PlayEffectSound failed: No SoundBase assigned."));
//	}
//
//	UGameplayStatics::PlaySoundAtLocation(
//		this,
//		EffectSound,
//		FVector(100, 200, 300),
//		FRotator::ZeroRotator,
//		1.0f,
//		1.0f,
//		0.0f,
//		EffectSoundAttenuation,
//		nullptr,
//		true
//	);
//
//	/*UAudioComponent* AudioComponent = GetOwner()->GetComponentByClass<UAudioComponent>();
//	if (!AudioComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UCollisionEffectComponent::PlayEffectSound failed: Cannot get audio component from owner."));
//	}
//
//	AudioComponent->SetSound(EffectSound);
//	AudioComponent->Play();*/
//}

//void UCollisionEffectComponent::CreateEffectInstance()
//{
//	//if (EffectClass)
//	//{
//	//	EffectInstance = NewObject<UEffect>(this, EffectClass);
//	//}
//}

