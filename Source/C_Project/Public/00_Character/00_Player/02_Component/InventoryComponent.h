// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "01_Item/ItemTypes.h"
#include "C_Project/C_Project.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAfterUseItem, FName, ItemCode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AConsumeActor;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//구조체 포인터는 UPROPERTY와 UFUNCTION 을 사용하지 못합니다.
	//아이템 코드를 키로 하여 맵에다 저장합니다.
	UPROPERTY(VisibleAnywhere)
		TMap<FName, FGenericItemInformation> Inventory;
	//퀵슬롯에 등록된 아이템코드가 저장됩니다.
	UPROPERTY(VisibleAnywhere)
		TArray<FName> QuickSlotArray;

public:

	const TMap<FName, FGenericItemInformation>& GetInventory() { return Inventory; }

	//아이템을 추가합니다.
	UFUNCTION(BlueprintCallable)
		void AddItem(class AActor* Item);

	//아이템 사용 후 호출되는 델리게이트입니다.
	UPROPERTY(BlueprintAssignable)
		FOnAfterUseItem OnAfterUseItem;


	/// <summary>
	/// Item_Code에 해당하는 아이템을 사용합니다.
	/// </summary>
	/// <param name="Item_Code">사용할 아이템 코드</param>
	/// <param name="Target">아이템 효과를 적용할 대상</param>
	UFUNCTION(BlueprintCallable)
		void UseItem(const FName Item_Code, AActor* Target);

	/**
	 * @brief 퀵슬롯 배열에 아이템을 등록합니다.
	 * @param ItemCode 등록할 아이템 코드
	 * @param SlotNumber 슬롯 번호
	 */
	void RegisterQuickItem(const FName& ItemCode, const int32& SlotNumber);

	/**
	 * @brief 해당 슬롯번
	 * @param SlotNumber 
	 */
	void UnRegisterQuickItem(const int32& SlotNumber);


	/**
	 * @brief 특정 슬롯에 들어있는 아이템을 사용합니다.
	 * @param SlotNumber 슬롯 번호
	 */
	void UseQuickItem(const int32& SlotNumber);

};
