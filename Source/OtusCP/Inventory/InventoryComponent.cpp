// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "PickupItem.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnOwnerBeginOverlap);
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetOwner()->OnActorBeginOverlap.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::GetItem(const FName ItemName, FInventoryItem& OutItem) const
{
	auto* FoundItem = ItemsTable ? ItemsTable->FindRow<FInventoryItem>(ItemName, TEXT("InventoryComponent::GetItem")) : nullptr;
	if (FoundItem)
	{
		OutItem = *FoundItem;
		return true;
	}

	return false;
}

void UInventoryComponent::AddItem(const FName ItemName, const int32 Count, const bool bRefreshInventory)
{
	if (Count <= 0)
	{
		return;
	}

	FInventoryItem OutItem;
	if (!GetItem(ItemName, OutItem))
	{
		return;
	}

	Items.FindOrAdd(ItemName) += Count;

	if (bRefreshInventory)
	{
		OnItemsUpdated.Broadcast();
	}
}

bool UInventoryComponent::RemoveItem(const FName ItemName, const int32 Count, const bool bRefreshInventory)
{
	if (Count <= 0)
	{
		return false;
	}

	auto* FoundItem = Items.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return false;
	}

	if (*FoundItem == Count)
	{
		Items.Remove(ItemName);
	}
	else if (*FoundItem < Count)
	{
		return false;
	}
	else
	{
		*FoundItem -= Count;
	}

	if (bRefreshInventory)
	{
		OnItemsUpdated.Broadcast();
	}

	return true;
}

bool UInventoryComponent::GetRecipe(const FName RecipeName, FInventoryRecipe& OutRecipe) const
{
	if (auto* FoundRecipe = Recipes.Find(RecipeName))
	{
		OutRecipe = *FoundRecipe;
		return true;
	}

	return false;
}

bool UInventoryComponent::CraftItem(const FName RecipeName)
{
	FInventoryRecipe Recipe;
	if (!GetRecipe(RecipeName, Recipe))
	{
		return false;
	}

	for (const auto& [Item, Count] : Recipe.RequestedItems)
	{
		if (Items.FindRef(Item.Item.RowName) < Count)
		{
			return false;
		}
	}

	for (const auto& [Item, Count] : Recipe.RequestedItems)
	{
		//if (!RemoveItem(Item.GetRowName(), Count, false))
		if (!RemoveItem(Item.Item.RowName, Count, false))
		{
			return false;
		}
	}

	AddItem(Recipe.CraftedItem.Item.RowName, Recipe.CraftedCount);

	return true;
}

void UInventoryComponent::OnOwnerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (auto* PickupItem = Cast<APickupItem>(OtherActor))
	{
		AddItem(PickupItem->PickupItem.RowName, PickupItem->PickupCount);
		OtherActor->Destroy();
	}
}
