// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/99_DragAndDrop/DragShadowWidget.h"
#include "Components/SizeBox.h"

void UDragShadowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DraggedWidget != nullptr)
	{
		auto size = DraggedWidget->GetDesiredSize();

		SizeBox_Override->SetHeightOverride(size.Y);
		SizeBox_Override->SetWidthOverride(size.X);
	}
}
