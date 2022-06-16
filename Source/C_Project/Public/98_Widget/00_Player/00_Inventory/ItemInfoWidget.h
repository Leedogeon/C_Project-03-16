// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemType;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;


	UPROPERTY()
		class UImage* Image_ItemImage;


	UPROPERTY()
		class UTextBlock* TextBlock_ItemDescription;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemDescription_Long;


	UPROPERTY(EditAnywhere)
		class UTexture2D* DefaultItemImage;

	virtual void NativeConstruct() override;

	void Init();
public:
	UFUNCTION()
		void SetInfo(const FName& ItemCode);
};
