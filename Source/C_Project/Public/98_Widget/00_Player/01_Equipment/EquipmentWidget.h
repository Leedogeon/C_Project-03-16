// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UImage* Image_Player;
	UPROPERTY()
		class UVerticalBox* VerticalBox_Armors;
	UPROPERTY()
		class UVerticalBox* VerticalBox_Weapons;


	UPROPERTY()
		class UTextBlock* TextBlock_HP;
	UPROPERTY()
		class UTextBlock* TextBlock_SP;


	UPROPERTY()
		class UTextBlock* TextBlock_Damage;
	UPROPERTY()
		class UTextBlock* TextBlock_Defence;


	UPROPERTY()
		class UTextBlock* TextBlock_Str;
	UPROPERTY()
		class UTextBlock* TextBlock_Dex;
	UPROPERTY()
		class UTextBlock* TextBlock_Wiz;


	UPROPERTY()
		class UHorizontalBox* HorizontalBox_Quick;


	UPROPERTY()
		class UItemListWidget* UMG_ItemList;
	UPROPERTY()
		class UButton* Button_Close;


	//툴팁위젯으로 사용할 블루프린트 위젯 오브젝트
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UEquipmentToolTipWidget> EquipmentToolTipWidgetObject;
	//위 변수로 생성된 위젯을 저장할 변수
	UPROPERTY()
		UEquipmentToolTipWidget* EquipmentToolTipWidget;
public:

	UEquipmentToolTipWidget* GetEquipmentToolTipWidget() { return EquipmentToolTipWidget; }
	/**
	 * @brief 특정 위젯에 툴팁을 설정합니다.
	 * @param Widget 툴팁을 설정할 위젯
	 */
	void SetToolTip(UUserWidget* Widget);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	//능력치가 변하면 델리게이트를 통해서 호출됩니다.
	UFUNCTION()
		void UpdateStatusInfo(class UStatusComponent* StatComp);
};

