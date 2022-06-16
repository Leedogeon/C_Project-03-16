// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/00_Inventory/InventoryWidget.h"
#include "98_Widget/00_Player/00_Inventory/ItemListWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMG_ItemList->SetItemInfoWidget(UMG_ItemInfo);
}
