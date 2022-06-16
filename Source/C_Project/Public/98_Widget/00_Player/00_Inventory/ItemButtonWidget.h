// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemTypes.h"
#include "98_Widget/00_Player/99_DragAndDrop/DragWidget.h"

#include "ItemButtonWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoveredItemButton, const FName&, ItemCode);

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemButtonType : uint8
{
	INVENTORY,
	EQUIPMENT
};

UCLASS()
class C_PROJECT_API UItemButtonWidget : public UDragWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class UBorder* Border_Button;
	UPROPERTY()
		class UImage* Image_ItemImage;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemDescription;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemCount;

	//이 위젯 위에 마우스가 올라왔을 때 변경할 색입니다.
	UPROPERTY(EditAnywhere)
		FLinearColor HoverdColor;

	//이 버튼이 표시하고 있는 아이템의 코드입니다.
	UPROPERTY()
		FName Item_Code;

	//이 버튼이 인벤토리에 의해서 생성되었는가 혹은 장비창에 의해서 생성되었는가 정의하는 변수입니다.
	UPROPERTY()
		EItemButtonType ItemButtonType = EItemButtonType::INVENTORY;
	//마우스를 올렸을 때 사용할 사운드
	UPROPERTY(EditAnywhere)
		class USoundBase* HoveredSound;
public:
	FName GetItemCode() { return Item_Code; }
	void SetInfo(const FGenericItemInformation& Info, EItemButtonType type = EItemButtonType::INVENTORY);

	UPROPERTY(BlueprintAssignable)
		FOnHoveredItemButton OnHoveredItemButton;


protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
