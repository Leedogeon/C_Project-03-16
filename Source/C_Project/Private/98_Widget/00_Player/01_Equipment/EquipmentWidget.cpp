// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/01_Equipment/EquipmentWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/ItemTypes.h"
#include "98_Widget/00_Player/01_Equipment/EquipButtonWidget.h"
#include "Components/VerticalBox.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "98_Widget/00_Player/00_Inventory/ItemListWidget.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentItemListWidget.h"
#include "Components/TextBlock.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentToolTipWidget.h"
#include "Components/HorizontalBox.h"

void UEquipmentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	int32 SlotNumber = 0;
	for (auto i = 0; i < HorizontalBox_Quick->GetChildrenCount(); i++)
	{
		auto button = Cast<UEquipButtonWidget>(HorizontalBox_Quick->GetChildAt(i));
		if (button != nullptr)
		{
			button->SetButtonType(EEquipmentButtonType::QUICKSLOT);
			button->SetSlotNumber(SlotNumber);
			SlotNumber++;
			SetToolTip(button);
		}
	}
}


void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(0))->SetEquipmentType(EEquipmentType::HELMET);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(0)));
	

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(1))->SetEquipmentType(EEquipmentType::SHOULDER);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(1)));

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(2))->SetEquipmentType(EEquipmentType::ARMOR);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(2)));

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(3))->SetEquipmentType(EEquipmentType::GLOVE);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(3)));

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(4))->SetEquipmentType(EEquipmentType::BELT);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(4)));

	Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(5))->SetEquipmentType(EEquipmentType::SHOES);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Armors->GetChildAt(5)));






	Cast<UEquipButtonWidget>(VerticalBox_Weapons->GetChildAt(0))->SetEquipmentType(EEquipmentType::WEAPON);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Weapons->GetChildAt(0)));


	Cast<UEquipButtonWidget>(VerticalBox_Weapons->GetChildAt(1))->SetEquipmentType(EEquipmentType::SHIELD);
	SetToolTip(Cast<UEquipButtonWidget>(VerticalBox_Weapons->GetChildAt(1)));



	GetOwningPlayerPawn<APlayerCharacter>()->OnChangeStatusValue.AddUniqueDynamic(this, &UEquipmentWidget::UpdateStatusInfo);


	if(UMG_ItemList->IsA<UEquipmentItemListWidget>())
	{
		Cast<UEquipmentItemListWidget>(UMG_ItemList)->SetParentEquipmentWidget(this);
	}

}

void UEquipmentWidget::UpdateStatusInfo(UStatusComponent* StatComp)
{
	if (StatComp != nullptr)
	{
		const auto& StatusValue = StatComp->GetStatusValue();

		FString HP = FString::FormatAsNumber(StatusValue.HP) + "/" + FString::FormatAsNumber(StatusValue.MaxHP);
		TextBlock_HP->SetText(FText::FromString(HP));


		FString SP = FString::FormatAsNumber(StatusValue.SP) + "/" + FString::FormatAsNumber(StatusValue.MaxSP);
		TextBlock_SP->SetText(FText::FromString(SP));

		TextBlock_Damage->SetText(FText::AsNumber(StatusValue.Damage));
		TextBlock_Defence->SetText(FText::AsNumber(StatusValue.Defence));

		TextBlock_Str->SetText(FText::AsNumber(StatusValue.Str));
		TextBlock_Dex->SetText(FText::AsNumber(StatusValue.Dex));
		TextBlock_Wiz->SetText(FText::AsNumber(StatusValue.Wiz));
	}
}

void UEquipmentWidget::SetToolTip(UUserWidget* Widget)
{
	if (Widget != nullptr && EquipmentToolTipWidgetObject != nullptr)
	{

		if (EquipmentToolTipWidget == nullptr) {
			EquipmentToolTipWidget = CreateWidget<UEquipmentToolTipWidget>(GetOwningPlayer(), EquipmentToolTipWidgetObject);
		}

		if (EquipmentToolTipWidget != nullptr) {
			Widget->SetToolTip(EquipmentToolTipWidget);

			if (Widget->IsA<UEquipButtonWidget>()) {
				Cast<UEquipButtonWidget>(Widget)->OnHoveredEquipButton.AddUniqueDynamic(EquipmentToolTipWidget, &UEquipmentToolTipWidget::SetToolTipInfo);
			}

			if(Widget->IsA<UItemButtonWidget>())
			{
				Cast<UItemButtonWidget>(Widget)->OnHoveredItemButton.AddUniqueDynamic(EquipmentToolTipWidget, &UEquipmentToolTipWidget::SetToolTipInfo);
			}
		}
	}
}

