// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/99_DragAndDrop/DragWidget.h"
#include "98_Widget/00_Player/99_DragAndDrop/DragShadowWidget.h"
#include "98_Widget/00_Player/99_DragAndDrop/CommonDragDropOperation.h"
#include "Blueprint/SlateBlueprintLibrary.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

void UDragWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

void UDragWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (DragShadowWidgetObject != nullptr) {
		//DragShadowWidget = CreateWidget<UDragShadowWidget>(GetOwningPlayer(), DragShadowWidgetObject);
		//DragShadowWidget->DraggedWidget = this;

		auto DragOper =
			Cast<UCommonDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(CommonDragDropOperationObject));
		if(DragOper!=nullptr)
		{
			DragOper->DraggedWidget = this;
			DragOper->DragOffset = DragOffset;

			//DragOper->DefaultDragVisual = DragShadowWidget;
			DragOper->DefaultDragVisual = this;
			DragOper->Pivot = EDragPivot::MouseDown;

			OutOperation = DragOper;
		}

	}
}

FReply UDragWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	DragOffset = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, InMouseEvent.GetScreenSpacePosition());
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
