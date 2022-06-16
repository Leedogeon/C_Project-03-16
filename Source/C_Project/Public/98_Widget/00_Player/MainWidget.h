// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 플레이어에게 부착될 메인 위젯입니다.
 */
UCLASS()
class C_PROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//플레이어 프로그래스 정보를 표시
	UPROPERTY()
		class UPlayerProgressWidget* UMG_PlayerProgress;
	//인벤토리
	UPROPERTY()
		class UInventoryWidget* UMG_Inventory;
	//장비
	UPROPERTY()
		class UEquipmentWidget* UMG_Equipment;

	//인벤토리를 열 때 재생할 사운드
	UPROPERTY(EditAnywhere)
		class USoundBase* InventoryOpenSound;
	//장비창을 열 때 재생할 사운드
	UPROPERTY(EditAnywhere)
		class USoundBase* EquipmentOpenSound;
public:

	UFUNCTION()
		void UpdateHPPercent(class UStatusComponent* StatComp);
	UFUNCTION()
		void UpdateSPPercent(class UStatusComponent* StatComp);

	void OpenInventory();
	void OpenEquipment();

	//이 위젯에 드롭다운된 경우 해당 위젯의 위치를 옮깁니다.
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
