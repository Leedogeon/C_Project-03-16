// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemListWidget.generated.h"

enum class EEquipmentType : uint8;
/**
 * 
 */
UCLASS()
class C_PROJECT_API UItemListWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UButton* Button_All;
	UPROPERTY()
		class UButton* Button_Consume;
	UPROPERTY()
		class UButton* Button_Armor;
	UPROPERTY()
		class UButton* Button_Glove;
	UPROPERTY()
		class UButton* Button_Belt;
	UPROPERTY()
		class UButton* Button_Helmet;
	UPROPERTY()
		class UButton* Button_Shoes;
	UPROPERTY()
		class UButton* Button_Shoulder;
	UPROPERTY()
		class UButton* Button_Weapon;
	UPROPERTY()
		class UButton* Button_Shield;

	UFUNCTION()
		void OnClickedAllButton();

	UFUNCTION()
		virtual void OnClickedConsumeButton();

	UFUNCTION()
		void OnClickedArmorButton();

	UFUNCTION()
		void OnClickedGloveButton();

	UFUNCTION()
		void OnClickedBeltButton();

	UFUNCTION()
		void OnClickedHelmetButton();

	UFUNCTION()
		void OnClickedShoesButton();

	UFUNCTION()
		void OnClickedShoulderButton();

	UFUNCTION()
		void OnClickedWeaponButton();

	UFUNCTION()
		void OnClickedShieldButton();

	UPROPERTY()
		class UScrollBox* ScrollBox_ItemList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemButtonWidget> ItemButtonWidgetObject;

	virtual void NativeConstruct() override;

	UFUNCTION()
		virtual void CreateItemList();
	/// <summary>
	/// 아이템 코드에 해당하는 아이템으로 버튼 정보를 업데이트 합니다.
	/// </summary>
	UFUNCTION()
		virtual void ButtonUpdate(FName ItemCode);

	/**
	 * @brief 파라미터로 전달된 타입에 맞는 리스트를 생성합니다.
	 * @param Type 생성할 장비 타입
	 */
	virtual void CreateEquipmentItemList(EEquipmentType Type);


	UPROPERTY()
		class UItemInfoWidget* UMG_ItemInfo;

public:
	void SetItemInfoWidget(class UItemInfoWidget* InfoWidget) { UMG_ItemInfo = InfoWidget; }
};


