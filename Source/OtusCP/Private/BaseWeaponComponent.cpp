// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponComponent.h"

UBaseWeaponComponent::UBaseWeaponComponent()
{
	ShootSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ShootSocket"));
}

void UBaseWeaponComponent::StartShoot_Implementation(FVector AimLocation)
{
	
}

void UBaseWeaponComponent::StopShoot_Implementation()
{

}