// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseWeapon::ABaseWeapon(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ShootSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ShootSocket"));
	ShootSocket->SetupAttachment(RootComponent);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::StartShoot_Implementation()
{
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ABaseWeapon::ShootLoop, 1/WeaponSettings.FireRate, true, 0);
}

void ABaseWeapon::ShootLoop()
{
	FVector AimLocation;
	if(PlayerCameraManager!=nullptr)
	{
		AimLocation = PlayerCameraManager->GetCameraLocation() + PlayerCameraManager->GetActorForwardVector()*2000;
	}
	else
	{
		AimLocation = this->GetActorLocation() + this->GetActorForwardVector()*2000;
	}
		FVector SpawnLoc = ShootSocket->GetComponentLocation();
		FRotator SpawnRot = UKismetMathLibrary::MakeRotFromX(AimLocation - SpawnLoc);
		GetWorld()->SpawnActor(Projectile, &SpawnLoc, &SpawnRot); 
		OnShoot();
}


void ABaseWeapon::StopShoot_Implementation()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}
