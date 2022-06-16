// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	QuickSlotArray.SetNum(5);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UInventoryComponent::AddItem(AActor* Item)
{
	AItemActor* I = Cast<AItemActor>(Item);
	if (I != nullptr)
	{
		auto Code = I->GetItem_Code();
		auto ItemInfo = I->GetGenericItemInformation();


		if (ItemInfo.Item_Count <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Item Count is zero"));
			Item->Destroy();
			return;
		}

	

		if (!Inventory.Contains(Code)) {
			Inventory.Emplace(Code, ItemInfo);
		}
		else
		{
			Inventory[Code].Item_Count += ItemInfo.Item_Count;
		}


		FString str = "Add Item : " + Code.ToString();
		UKismetSystemLibrary::PrintString(this, *str);

		Item->Destroy();

	}
}

void UInventoryComponent::UseItem(const FName Item_Code, AActor* Target)
{
	if(Inventory.Contains(Item_Code))
	{
		FGenericItemInformation Info = Inventory[Item_Code];
		if(Info.Item_Count <= 0)
		{
			Inventory.Remove(Info.Item_Code);
			return;
		}



		if(Info.ItemActorObject != nullptr)
		{
			FActorSpawnParameters Param;
			Param.Owner = GetOwner();
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AItemActor* Item = GetWorld()->SpawnActor<AItemActor>(Info.ItemActorObject, FTransform(), Param);
			if (Item != nullptr)
			{
				Item->ApplyItem(Target);
			}
		}

		OnAfterUseItem.Broadcast(Item_Code);

	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Find Item : %s"),*Item_Code.ToString());
	}
}

void UInventoryComponent::RegisterQuickItem(const FName& ItemCode, const int32& SlotNumber)
{
	if(Inventory.Contains(ItemCode))
	{
		QuickSlotArray[SlotNumber] = ItemCode;
	}
}

void UInventoryComponent::UnRegisterQuickItem(const int32& SlotNumber) {
	
	if (QuickSlotArray.IsValidIndex(SlotNumber)) {
		QuickSlotArray[SlotNumber] = NAME_None;
	}

}

void UInventoryComponent::UseQuickItem(const int32& SlotNumber)
{
	if (QuickSlotArray.IsValidIndex(SlotNumber)) {

		UseItem(QuickSlotArray[SlotNumber], GetOwner());
	}
}


