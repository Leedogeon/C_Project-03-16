// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenEquipment);
/**
 * 
 */
UCLASS()
class C_PROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	//각종 주요 위젯이 포함된 메인 위젯 블루프린트 오브젝트입니다. 이 오브젝트 정보로 위젯을 생성합니다.
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> MainWidgetObject;
	//위 변수로 받아온 블루프린트 오브젝트에서 생성한 위젯 포인터입니다.
	UPROPERTY()
		UMainWidget* MainWidget;


	//락온에 사용할 위젯 오브젝트입니다.
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LockOnWidgetObject;
	UPROPERTY()
		class UUserWidget* LockOnWidget;

	//컨트롤러가 해당 폰에 빙의되는 시점에 호출됨.
	virtual void OnPossess(APawn* aPawn) override;

	/// <summary>
	/// 특정 대상이 락온되었을때 호출되는 함수입니다.
	/// </summary>
	UFUNCTION()
		void OnTargetLockOnEvent(AActor* Target);
	/// <summary>
	/// 타겟의 위치로 위젯의 위치를 업데이트 합니다.
	/// </summary>
	UFUNCTION()
		void OnLockOnWigetPosUpdateEvent(AActor* Target);

	/// <summary>
	/// 락온이 해제되면 호출됩니다.
	/// </summary>
	UFUNCTION()
		void OnEndLockOnEvent();
public:
	UMainWidget* GetMainWidget() { return MainWidget; }

	//인벤토리가 열리거나 닫힐 때 호출
	UPROPERTY(BlueprintAssignable)
		FOnOpenInventory OnOpenInventory;
	//장비창이 열리거나 닫힐 때 호출
	UPROPERTY(BlueprintAssignable)
		FOnOpenEquipment OnOpenEquipment;
protected:

	UFUNCTION()
		void OnOpenInventoryEvent();
	UFUNCTION()
		void OnOpenEquipmentEvent();
};
