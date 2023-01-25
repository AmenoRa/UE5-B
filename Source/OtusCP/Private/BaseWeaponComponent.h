// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class UBaseWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

	UBaseWeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ShootSocket;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartShoot(FVector AimLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopShoot();
};
