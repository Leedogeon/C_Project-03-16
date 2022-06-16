// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "98_Widget/00_Player/00_Inventory/ItemButtonWidget.h"
#include "Blueprint/UserWidget.h"
#include "EquipButtonWidget.generated.h"

enum class EEquipmentType : uint8;
/**
 * 
 */

UENUM(BlueprintType)
enum class EEquipmentButtonType : uint8
{
	EQUIPMENT,
	QUICKSLOT
};



UCLASS()
class C_PROJECT_API UEquipButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		EEquipmentButtonType EquipmentButtonType;

	UPROPERTY()
		class UImage* Image_Button;
	UPROPERTY(EditAnywhere)
		class UTexture2D* ButtonImage;
	UPROPERTY()
		FName ItemCode;
	UPROPERTY()
		EEquipmentType EquipmentType;
	UPROPERTY()
		int32 SlotNumber;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;


	UPROPERTY(EditAnywhere)
		FLinearColor HoveredColor;
	UPROPERTY(EditAnywhere)
		class USoundBase* HoveredSound;
	UPROPERTY(EditAnywhere)
		class USoundBase* EquipSound;
	UPROPERTY(EditAnywhere)
		class USoundBase* UnEquipSound;

	virtual void NativePreConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	UFUNCTION()
		void UpdateQuickButtonEvent(FName Code);

public:
	void SetEquipmentType(EEquipmentType type) { EquipmentType = type; }
	void SetButtonType(EEquipmentButtonType type) { EquipmentButtonType = type; }
	void SetSlotNumber(const int32& number) { SlotNumber = number; }

	UPROPERTY(BlueprintAssignable)
		FOnHoveredItemButton OnHoveredEquipButton;
};
