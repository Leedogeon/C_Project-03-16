// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


/**
 * 
 */
UCLASS()
class C_PROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UItemListWidget* UMG_ItemList;
	UPROPERTY()
		class UItemInfoWidget* UMG_ItemInfo;

	UPROPERTY()
		class UButton* Button_Close;

	virtual void NativeConstruct() override;
};
