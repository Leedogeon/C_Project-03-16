// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "98_Widget/00_Player/00_Inventory/ItemListWidget.h"
#include "EquipmentItemListWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UEquipmentItemListWidget : public UItemListWidget
{
	GENERATED_BODY()

protected:

	virtual void OnClickedConsumeButton() override;
	virtual void CreateItemList() override;
	virtual void CreateEquipmentItemList(EEquipmentType Type) override;
	virtual void ButtonUpdate(FName ItemCode) override { };

	//이 위젯으로 생성된 버튼들에게 툴팁을 설정해주기 위해서 어쩔수 없이 이 위젯의 부모를 받아와 이 변수에 저장합니다.
	UPROPERTY()
		class UEquipmentWidget* UMG_Equipment;
public:
	void SetParentEquipmentWidget(class UEquipmentWidget* Widget) { UMG_Equipment = Widget; }
};
