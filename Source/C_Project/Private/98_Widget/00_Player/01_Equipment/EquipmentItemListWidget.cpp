// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/01_Equipment/EquipmentItemListWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentToolTipWidget.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UEquipmentItemListWidget::OnClickedConsumeButton()
{
	ScrollBox_ItemList->ClearChildren();

	if (ItemButtonWidgetObject != nullptr) {

		auto Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();

		for (TMap<FName, FGenericItemInformation>::TConstIterator iter = Inventory.CreateConstIterator(); iter; ++iter)
		{
			FGenericItemInformation info = iter.Value();

			if (info.Item_Type == EItemType::CONSUME) {

				auto Button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), ItemButtonWidgetObject);
				if (Button != nullptr)
				{
					UMG_Equipment->SetToolTip(Button);
					Button->OnHoveredItemButton.AddUniqueDynamic(UMG_Equipment->GetEquipmentToolTipWidget(), &UEquipmentToolTipWidget::SetToolTipInfo);
					Button->SetInfo(info, EItemButtonType::EQUIPMENT);
					ScrollBox_ItemList->AddChild(Button);
				}
			}
		}

	}
}

void UEquipmentItemListWidget::CreateItemList()
{
	ScrollBox_ItemList->ClearChildren();

	if (ItemButtonWidgetObject != nullptr) {

		auto Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();


		for (TMap<FName, FGenericItemInformation>::TConstIterator iter = Inventory.CreateConstIterator(); iter; ++iter)
		{
			FGenericItemInformation info = iter.Value();

			auto Button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), ItemButtonWidgetObject);
			if (Button != nullptr)
			{
				UMG_Equipment->SetToolTip(Button);
				Button->OnHoveredItemButton.AddUniqueDynamic(UMG_Equipment->GetEquipmentToolTipWidget(), &UEquipmentToolTipWidget::SetToolTipInfo);
				Button->SetInfo(info, EItemButtonType::EQUIPMENT);
				ScrollBox_ItemList->AddChild(Button);
			}
		}

	}
}

void UEquipmentItemListWidget::CreateEquipmentItemList(EEquipmentType Type)
{
	ScrollBox_ItemList->ClearChildren();

	if (ItemButtonWidgetObject != nullptr) {

		auto Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();

		for (TMap<FName, FGenericItemInformation>::TConstIterator iter = Inventory.CreateConstIterator(); iter; ++iter)
		{
			FGenericItemInformation info = iter.Value();

			if (info.Item_Type == EItemType::EQUIPMENT) {

				if (info.P_ItemInfo.IsValid()) {

					FEquipment* Equipment = (FEquipment*)info.P_ItemInfo.Get();
					if (Equipment != nullptr && Equipment->Equipment_Type == Type) {

						auto Button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), ItemButtonWidgetObject);
						if (Button != nullptr)
						{
							UMG_Equipment->SetToolTip(Button);
							Button->OnHoveredItemButton.AddUniqueDynamic(UMG_Equipment->GetEquipmentToolTipWidget(), &UEquipmentToolTipWidget::SetToolTipInfo);
							Button->SetInfo(info, EItemButtonType::EQUIPMENT);
							ScrollBox_ItemList->AddChild(Button);
						}
					}
				}
			}
		}

	}
}
