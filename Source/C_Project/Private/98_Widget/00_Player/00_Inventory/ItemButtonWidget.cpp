// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UItemButtonWidget::SetInfo(const FGenericItemInformation& Info, EItemButtonType type)
{

	ItemButtonType = type;

	Item_Code = Info.Item_Code;

	Image_ItemImage->SetBrushFromTexture(Info.Item_Image);
	TextBlock_ItemName->SetText(FText::FromString(Info.Item_Name));
	TextBlock_ItemDescription->SetText(FText::FromString(Info.Item_Description));
	TextBlock_ItemCount->SetText(FText::AsNumber(Info.Item_Count));

}

void UItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

void UItemButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	FSlateBrush Brush;
	Brush.TintColor = HoverdColor;

	Border_Button->SetBrush(Brush);
	UGameplayStatics::SpawnSound2D(GetOwningPlayer(), HoveredSound);
	OnHoveredItemButton.Broadcast(Item_Code);
}

 void UItemButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	 Super::NativeOnMouseLeave(InMouseEvent);

	 FSlateBrush Brush;
	 Brush.TintColor = FLinearColor::Black;

	 Border_Button->SetBrush(Brush);
}

FReply UItemButtonWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	 Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	 if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {

		 auto Player = GetOwningPlayerPawn<APlayerCharacter>();
		 auto InvenComp = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();

		 auto inventory = InvenComp->GetInventory();
		 if (inventory.Contains(Item_Code) && inventory[Item_Code].Item_Type == EItemType::CONSUME)
		 {
			 InvenComp->UseItem(Item_Code, Player);
		 }
	 }
	 
	 return FReply::Handled();

 }

FReply UItemButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (ItemButtonType == EItemButtonType::INVENTORY) {
		return FReply::Handled();
	}
	else {
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
}
