// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/00_Inventory/ItemListWidget.h"
#include "Components/ScrollBox.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/MainPlayerController.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "98_Widget/00_Player/00_Inventory/ItemInfoWidget.h"
#include "Components/Button.h"

void UItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateItemList();

	GetOwningPlayer<AMainPlayerController>()->OnOpenInventory.AddUniqueDynamic(this, &UItemListWidget::CreateItemList);
	GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->OnAfterUseItem.AddUniqueDynamic(this, &UItemListWidget::ButtonUpdate);

	Button_All->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedAllButton);
	Button_Consume->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedConsumeButton);
	Button_Armor->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedArmorButton);
	Button_Glove->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedGloveButton);
	Button_Belt->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedBeltButton);
	Button_Helmet->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedHelmetButton);
	Button_Shoes->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedShoesButton);
	Button_Shoulder->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedShoulderButton);
	Button_Weapon->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedWeaponButton);
	Button_Shield->OnClicked.AddUniqueDynamic(this, &UItemListWidget::OnClickedShieldButton);
}

void UItemListWidget::OnClickedAllButton()
{
	CreateItemList();
}

void UItemListWidget::OnClickedConsumeButton()
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
					Button->SetInfo(info);
					Button->OnHoveredItemButton.AddUniqueDynamic(UMG_ItemInfo, &UItemInfoWidget::SetInfo);
					ScrollBox_ItemList->AddChild(Button);
				}
			}
		}

	}
}

void UItemListWidget::OnClickedArmorButton()
{
	CreateEquipmentItemList(EEquipmentType::ARMOR);
}

void UItemListWidget::OnClickedGloveButton()
{
	CreateEquipmentItemList(EEquipmentType::GLOVE);
}

void UItemListWidget::OnClickedBeltButton()
{
	CreateEquipmentItemList(EEquipmentType::BELT);
}

void UItemListWidget::OnClickedHelmetButton()
{
	CreateEquipmentItemList(EEquipmentType::HELMET);
}

void UItemListWidget::OnClickedShoesButton()
{
	CreateEquipmentItemList(EEquipmentType::SHOES);
}

void UItemListWidget::OnClickedShoulderButton()
{
	CreateEquipmentItemList(EEquipmentType::SHOULDER);
}

void UItemListWidget::OnClickedWeaponButton()
{
	CreateEquipmentItemList(EEquipmentType::WEAPON);
}

void UItemListWidget::OnClickedShieldButton()
{
	CreateEquipmentItemList(EEquipmentType::SHIELD);
}

void UItemListWidget::CreateItemList()
{
	ScrollBox_ItemList->ClearChildren();

	if (ItemButtonWidgetObject != nullptr) {

		auto Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();


		for(TMap<FName, FGenericItemInformation>::TConstIterator iter = Inventory.CreateConstIterator(); iter; ++iter)
		{
			FGenericItemInformation info = iter.Value();

			auto Button = CreateWidget<UItemButtonWidget>(GetOwningPlayer(), ItemButtonWidgetObject);
			if(Button!=nullptr)
			{
				Button->SetInfo(info);
				Button->OnHoveredItemButton.AddUniqueDynamic(UMG_ItemInfo, &UItemInfoWidget::SetInfo);
				ScrollBox_ItemList->AddChild(Button);
			}
		}
		
	}
}

void UItemListWidget::ButtonUpdate(FName ItemCode)
{
	for(auto i = 0; i< ScrollBox_ItemList->GetChildrenCount();i++)
	{
		UItemButtonWidget* Button = Cast<UItemButtonWidget>(ScrollBox_ItemList->GetChildAt(i));
		if (Button != nullptr)
		{
			if(Button->GetItemCode().IsEqual(ItemCode))
			{
				auto InvenComp = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
				auto Inven = InvenComp->GetInventory();
				if(Inven.Contains(ItemCode))
				{
					Button->SetInfo(Inven[ItemCode]);
				}else
				{
					Button->RemoveFromParent();
				}
				break;
			}
		}
	}
}

void UItemListWidget::CreateEquipmentItemList(EEquipmentType Type)
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
							Button->SetInfo(info);
							Button->OnHoveredItemButton.AddUniqueDynamic(UMG_ItemInfo, &UItemInfoWidget::SetInfo);
							ScrollBox_ItemList->AddChild(Button);
						}
					}
				}
			}
		}

	}
}
