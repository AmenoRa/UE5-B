// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/DataTable.h"

#include "BaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSettingsStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage = 10;
};


UCLASS()
class ABaseWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ShootSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ShootLoop();

	FTimerHandle ShootTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponSettingsStruct WeaponSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	APlayerCameraManager* PlayerCameraManager;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartShoot();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopShoot();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShoot();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartAim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StopAim();
};
