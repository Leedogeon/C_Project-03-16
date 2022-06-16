// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/01_Equipment/EquipmentToolTipWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UEquipmentToolTipWidget::SetToolTipInfo(const FName& ItemCode)
{
	if(GetOwningPlayer() == nullptr || GetOwningPlayerPawn() == nullptr)
	{
		return;
	}

	const auto& Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();
	if (Inventory.Contains(ItemCode)) {
		const auto& Item = Inventory[ItemCode];
		Image_Item->SetBrushFromTexture(Item.Item_Image);
		TextBlock_ItemName->SetText(FText::FromString(Item.Item_Name));

		if (Item.P_ItemInfo.IsValid())
		{
			if (Item.Item_Type == EItemType::EQUIPMENT) {

				auto Equip = (FEquipment*)(Item.P_ItemInfo.Get());
				TextBlock_Dam->SetText(FText::AsNumber(Equip->Damage));
				TextBlock_Def->SetText(FText::AsNumber(Equip->Defence));
				TextBlock_ActionSpeed->SetText(FText::AsNumber(Equip->ActionSpeed));

				TextBlock_MaxHP->SetText(FText::AsNumber(Equip->MaxHP));

				TextBlock_Str->SetText(FText::AsNumber(Equip->Str));
				TextBlock_Dex->SetText(FText::AsNumber(Equip->Dex));
				TextBlock_Wiz->SetText(FText::AsNumber(Equip->Wiz));

				TextBlock_MaxSP->SetText(FText::AsNumber(Equip->MaxSP));
				TextBlock_ItemDescription->SetText(FText::FromString("-"));
			}
			else
			{
	
				TextBlock_Dam->SetText(FText::FromString("-"));
				TextBlock_Def->SetText(FText::FromString("-"));
				TextBlock_ActionSpeed->SetText(FText::FromString("-"));

				TextBlock_MaxHP->SetText(FText::FromString("-"));

				TextBlock_Str->SetText(FText::FromString("-"));
				TextBlock_Dex->SetText(FText::FromString("-"));
				TextBlock_Wiz->SetText(FText::FromString("-"));

				TextBlock_MaxSP->SetText(FText::FromString("-"));

				TextBlock_ItemDescription->SetText(FText::FromString(Item.Item_Description));
			}
		}
	}
	else
	{
		Image_Item->SetBrushFromTexture(NoItemTexture);
		TextBlock_ItemName->SetText(FText::FromString("-"));
		TextBlock_Dam->SetText(FText::FromString("-"));
		TextBlock_Def->SetText(FText::FromString("-"));
		TextBlock_ActionSpeed->SetText(FText::FromString("-"));

		TextBlock_MaxHP->SetText(FText::FromString("-"));

		TextBlock_Str->SetText(FText::FromString("-"));
		TextBlock_Dex->SetText(FText::FromString("-"));
		TextBlock_Wiz->SetText(FText::FromString("-"));

		TextBlock_MaxSP->SetText(FText::FromString("-"));

		TextBlock_ItemDescription->SetText(FText::FromString("-"));

	}

}
