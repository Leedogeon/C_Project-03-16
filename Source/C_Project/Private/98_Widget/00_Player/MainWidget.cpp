// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/MainWidget.h"

#include "98_Widget/00_Player/PlayerProgressWidget.h"
#include "98_Widget/00_Player/00_Inventory/InventoryWidget.h"
#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "98_Widget/00_Player/01_Equipment/EquipmentWidget.h"
#include "Kismet/KismetSystemLibrary.h"


#include "Kismet/KismetInputLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "98_Widget/00_Player/99_DragAndDrop/CommonDragDropOperation.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainWidget::UpdateHPPercent(UStatusComponent* StatComp)
{
	UMG_PlayerProgress->UpdateProgressHP(StatComp);
}

void UMainWidget::UpdateSPPercent(UStatusComponent* StatComp)
{
	UMG_PlayerProgress->UpdateProgressSP(StatComp);
}

void UMainWidget::OpenInventory()
{
	if(UMG_Inventory!=nullptr)
	{

		if(UMG_Inventory->GetVisibility() == ESlateVisibility::Visible)
		{
			GetOwningPlayer()->bShowMouseCursor = false;
			GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
			UMG_Inventory->SetVisibility(ESlateVisibility::Hidden);
		}else
		{
			GetOwningPlayer()->bShowMouseCursor = true;
			GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
			UMG_Inventory->SetVisibility(ESlateVisibility::Visible);
			UGameplayStatics::SpawnSound2D(GetOwningPlayer(), InventoryOpenSound);
		}
	}
}

void UMainWidget::OpenEquipment()
{
	if(UMG_Equipment!=nullptr)
	{
		if (UMG_Equipment->GetVisibility() == ESlateVisibility::Visible)
		{
			GetOwningPlayer()->bShowMouseCursor = false;
			GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
			UMG_Equipment->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			GetOwningPlayer()->bShowMouseCursor = true;
			GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
			UMG_Equipment->SetVisibility(ESlateVisibility::Visible);
			UGameplayStatics::SpawnSound2D(GetOwningPlayer(), EquipmentOpenSound);
		}
	}
}

bool UMainWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if(InOperation != nullptr)
	{
		auto Oper = Cast<UCommonDragDropOperation>(InOperation);
		if(Oper!=nullptr)
		{
			if (Oper->DraggedWidget->IsA<UItemButtonWidget>() == false) {
				Oper->DraggedWidget->RemoveFromParent();

				Oper->DraggedWidget->SetPositionInViewport(
					USlateBlueprintLibrary::AbsoluteToLocal(InGeometry,
						UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InDragDropEvent)) - Oper->DragOffset, false);

				Oper->DraggedWidget->AddToViewport();

				return true;
			}
		}
	}


	return false;
}
