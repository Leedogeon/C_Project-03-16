// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.h"
#include "GameFramework/Actor.h"
#include "C_Project/C_Project.h"
#include "Engine/DataTable.h"
#include "ItemActor.generated.h"

/*
 *	레벨에서 획득 가능한 아이템 액터입니다.
 *	플레이어가 아이템 사용시 적용할 효과들도 이 액터 내부에 정의되어 있습니다.
 */
UCLASS()
class C_PROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:

	//플레이어와의 겹칩을 확인할 콜리전
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereComponent;
	//아이템 파티클
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* ParticleSystemComponent;
	//아이템을 줏을 수 있다는 UI 표시를 위한 위젯컴포넌트
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* WidgetComponent;

	//이 액터가 가지고 있는 아이템 코드
	UPROPERTY(EditAnywhere)
		FName Item_Code;
	//이 카운트 만큼 플레이어 인벤토리에 아이템 갯수가 추가됩니다.
	UPROPERTY(EditAnywhere)
		int32 Item_Count = 1;

	//모든 아이템 정보가 들어있는 데이터테이블입니다.
	UPROPERTY(EditAnywhere)
		class UDataTable* Item_Table;

	///아이템 공통 정보가 들어있는 구조체
	UPROPERTY(VisibleAnywhere)
		FGenericItemInformation GenericItemInformation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	#if WITH_EDITOR
	//블루프린트의 Construct와 같은 역할을 합니다.
	//이 블루프린트 오브젝트 내부 변수가 변경되면 호출됩니다.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	/**
	 * @brief 플레이어가 아이템 사용시와 같은 이 액터가 스폰되는경우,PostEditChangeProperty가 호출되지 않아 이 함수 내부에서 다시 내용을 초기화 합니다.
	 */
	virtual void PostInitializeComponents() override;
	/**
	 * @brief 데이터테이블에서 이 액터가 가진 아이템 코드를 키로 하여 아이템 정보를 가져옵니다. 가져온 아이템 정보는 GenericItemInformation변수에 저장됩니다.
	 *	또한 아이템 종류에 따라 저장되어야 할 정보가 다르기 때문에, 아이템 종류마다 이 함수를 재 정의 해야 합니다.
	 */
	virtual void InitItemInformation();


public:

	PROPERTY_GETTER(WidgetComponent, UWidgetComponent*);
	PROPERTY_GETTER(Item_Code, FName);
	PROPERTY_GETTER(GenericItemInformation, FGenericItemInformation);

	/**
	 * @brief 대상에게 아이템 효과를 적용합니다. 아이템 종류별로 재 정의해서 기능을 구현합니다.
	 * @param Target 대상
	 */
	UFUNCTION(BlueprintNativeEvent)
		void ApplyItem(class AActor* Target);
	virtual void ApplyItem_Implementation(class AActor* Target) {  }

protected:
	template<typename T>
	const T* GetItemInformation();

};

template <typename T>
const T* AItemActor::GetItemInformation()
{
	if(Item_Table!=nullptr)
	{
		return Item_Table->FindRow<T>(Item_Code, "Cannot Find");
	}

	return nullptr;
}
