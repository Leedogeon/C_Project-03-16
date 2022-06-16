// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/01_Equipment/EquipButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "98_Widget/00_Player/99_DragAndDrop/CommonDragDropOperation.h"
#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "Components/Image.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentToolTipWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UEquipButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(ButtonImage != nullptr)
	{
		Image_Button->SetBrushFromTexture(ButtonImage);
	}
}


void UEquipButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);


	FSlateBrush Brush = Image_Button->Brush;
	Brush.TintColor = HoveredColor;

	Image_Button->SetBrush(Brush);

	//Cast<UEquipmentToolTipWidget>(ToolTipWidget)->SetToolTipInfo(ItemCode);
	UGameplayStatics::SpawnSound2D(GetOwningPlayer(), HoveredSound);
	OnHoveredEquipButton.Broadcast(ItemCode);
}

void UEquipButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	FSlateBrush Brush = Image_Button->Brush;
	Brush.TintColor = FLinearColor::White;

	Image_Button->SetBrush(Brush);


}

FReply UEquipButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);


	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{

		if (EquipmentButtonType == EEquipmentButtonType::EQUIPMENT) {
			auto EquipComp = GetOwningPlayerPawn<APlayerCharacter>()->GetEquipmentComponent();
			EquipComp->UnEquip(ItemCode, EquipmentType);
		}
		else {
			//여기서 퀵슬롯인 경우에 인벤토리 컴포넌트 내부에 저장된 퀵슬롯 아이템 코드를 지워주는 작업을 해야 합니다.
			auto InvenComp = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
			InvenComp->UnRegisterQuickItem(SlotNumber);
		}

		UGameplayStatics::SpawnSound2D(GetOwningPlayer(), UnEquipSound);
		ItemCode = NAME_None;
		


		if (ButtonImage != nullptr)
		{
			Cast<UEquipmentToolTipWidget>(ToolTipWidget)->SetToolTipInfo(ItemCode);
			Image_Button->SetBrushFromTexture(ButtonImage);
		}

		TextBlock_ItemCount->SetText(FText::GetEmpty());

	}

	return FReply::Handled();
}

FReply UEquipButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

void UEquipButtonWidget::UpdateQuickButtonEvent(FName Code)
{
	if (ItemCode.IsEqual(Code)) {
		const auto& Inventory = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->GetInventory();
		if (Inventory.Contains(Code)) {
			TextBlock_ItemCount->SetText(FText::AsNumber(Inventory[Code].Item_Count));
		}
	}
}

bool UEquipButtonWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		auto Oper = Cast<UCommonDragDropOperation>(InOperation);
		if (Oper != nullptr)
		{

			if (Oper->DraggedWidget != nullptr)
			{
				UItemButtonWidget* Button = Cast<UItemButtonWidget>(Oper->DraggedWidget);
				if (Button != nullptr)
				{

					auto InvenComp = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
					const auto& Inventory = InvenComp->GetInventory();
					if (Inventory.Contains(Button->GetItemCode())) {
						const FGenericItemInformation& ItemInfo = Inventory[Button->GetItemCode()];


						if (EquipmentButtonType == EEquipmentButtonType::EQUIPMENT) {

							if (ItemInfo.Item_Type == EItemType::EQUIPMENT) {
								if (ItemInfo.P_ItemInfo.IsValid())
								{

									FEquipment* Equipment = (FEquipment*)(ItemInfo.P_ItemInfo.Get());
									if (Equipment->Equipment_Type == EquipmentType)
									{
										ItemCode = Button->GetItemCode();
										UGameplayStatics::SpawnSound2D(GetOwningPlayer(), EquipSound);
										InvenComp->UseItem(ItemCode, GetOwningPlayerPawn());
										Image_Button->SetBrushFromTexture(Inventory[ItemCode].Item_Image);

										return true;
									}
								}
							}
						}else
						{
							/*
							 *	아이템정보를 가져와서 이 버튼에 등록하세요.
							 */
							if (ItemInfo.Item_Type == EItemType::CONSUME) {
								if(ItemInfo.P_ItemInfo.IsValid())
								{
									FConsume* Consume = (FConsume*)(ItemInfo.P_ItemInfo.Get());
									UGameplayStatics::SpawnSound2D(GetOwningPlayer(), EquipSound);
									ItemCode = ItemInfo.Item_Code;
									Image_Button->SetBrushFromTexture(Inventory[ItemCode].Item_Image);
									TextBlock_ItemCount->SetText(FText::AsNumber(ItemInfo.Item_Count));

									InvenComp->OnAfterUseItem.AddUniqueDynamic(this, &UEquipButtonWidget::UpdateQuickButtonEvent);
									InvenComp->RegisterQuickItem(ItemCode, SlotNumber);
									return true;
								}
							}
						}
					}
				}
			}
		}

	}

	return false;
}
	
