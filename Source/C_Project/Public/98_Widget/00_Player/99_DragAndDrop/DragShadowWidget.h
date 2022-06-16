// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragShadowWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UDragShadowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class USizeBox* SizeBox_Override;
	UPROPERTY()
		FVector2D DragOffset;

public:
	UPROPERTY()
		class UUserWidget* DraggedWidget;

	virtual void NativeConstruct() override;
};
