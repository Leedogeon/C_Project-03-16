// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentToolTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UEquipmentToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UImage* Image_Item;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;

	UPROPERTY()
		class UTextBlock* TextBlock_Dam;
	UPROPERTY()
		class UTextBlock* TextBlock_Def;
	UPROPERTY()
		class UTextBlock* TextBlock_ActionSpeed;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxHP;
	UPROPERTY()
		class UTextBlock* TextBlock_Str;
	UPROPERTY()
		class UTextBlock* TextBlock_Dex;
	UPROPERTY()
		class UTextBlock* TextBlock_Wiz;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxSP;

	UPROPERTY(EditAnywhere)
		class UTexture2D* NoItemTexture;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemDescription;
public:
	UFUNCTION()
		void SetToolTipInfo(const FName& ItemCode);
};
