// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Consume/ConsumeActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"

void AConsumeActor::ApplyItem_Implementation(AActor* Target)
{

	if (Target != nullptr)
	{
		APlayerCharacter* Player =	GetOwner<APlayerCharacter>();
		if (Player != nullptr)
		{
			Player->GetInventoryComponent()->Inventory[GenericItemInformation.Item_Code].Item_Count--;

			if (Player->GetInventoryComponent()->Inventory[GenericItemInformation.Item_Code].Item_Count <= 0) {
				Player->GetInventoryComponent()->Inventory.Remove(GenericItemInformation.Item_Code);
			}
		}
	}

}
