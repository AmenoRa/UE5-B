// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};

// TMap<FName, FInventoryItem>

USTRUCT(BlueprintType)
struct FInventoryItemReference
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ShowOnlyInnerProperties, RowType = "/Script/OtusCP.InventoryItem"))
	FDataTableRowHandle Item;

	friend uint32 GetTypeHash(const FInventoryItemReference& A)
	{
		return HashCombine(GetTypeHash(A.Item.DataTable), GetTypeHash(A.Item.RowName));
	}
};

USTRUCT(BlueprintType)
struct FInventoryRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ForceInlineRow))
	TMap<FInventoryItemReference, int32> RequestedItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FInventoryItemReference CraftedItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CraftedCount = 0;
};