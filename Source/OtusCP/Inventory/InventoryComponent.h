// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UDataTable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	bool GetItem(const FName ItemName, FInventoryItem& OutItem) const;

	UFUNCTION(BlueprintCallable)
	void AddItem(const FName ItemName, const int32 Count, const bool bRefreshInventory = true);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(const FName ItemName, const int32 Count, const bool bRefreshInventory = true);

	UFUNCTION(BlueprintPure)
	bool GetRecipe(const FName RecipeName, FInventoryRecipe& OutRecipe) const;

	UFUNCTION(BlueprintCallable)
	bool CraftItem(const FName RecipeName);

	UFUNCTION()
	void OnOwnerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsTable = nullptr;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemsUpdated);

	UPROPERTY(BlueprintAssignable)
	FOnItemsUpdated OnItemsUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FInventoryRecipe> Recipes;
};
