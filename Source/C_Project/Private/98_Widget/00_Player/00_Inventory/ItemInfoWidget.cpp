// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/00_Inventory/ItemInfoWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UItemInfoWidget::Init()
{

	TextBlock_ItemName->SetText(FText::FromString("-"));
	TextBlock_ItemType->SetText(FText::FromString("-"));
	TextBlock_ItemCount->SetText(FText::GetEmpty());

	TextBlock_ItemDescription->SetText(FText::FromString("-"));
	TextBlock_ItemDescription_Long->SetText(FText::FromString("-"));


	Image_ItemImage->SetBrushFromTexture(DefaultItemImage);
}

void UItemInfoWidget::SetInfo(const FName& ItemCode)
{
	auto InvenComp = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
	if (InvenComp != nullptr)
	{
		auto Inventory = InvenComp->GetInventory();
		if(Inventory.Contains(ItemCode))
		{
			FGenericItemInformation Info = Inventory[ItemCode];
			switch (Info.Item_Type)
			{
			case EItemType::CONSUME:
				TextBlock_ItemType->SetText(FText::FromString(TEXT("소비")));
				break;
			case EItemType::EQUIPMENT:
				TextBlock_ItemType->SetText(FText::FromString(TEXT("장비")));
				break;
			case EItemType::ETC:
				TextBlock_ItemType->SetText(FText::FromString(TEXT("기타")));
				break;
			}

			TextBlock_ItemName->SetText(FText::FromString(Info.Item_Name));
			TextBlock_ItemCount->SetText(FText::AsNumber(Info.Item_Count));

			TextBlock_ItemDescription->SetText(FText::FromString(Info.Item_Description));
			TextBlock_ItemDescription_Long->SetText(FText::FromString(Info.Item_Description_Long));

			Image_ItemImage->SetBrushFromTexture(Info.Item_Image);
		}
	}
}
