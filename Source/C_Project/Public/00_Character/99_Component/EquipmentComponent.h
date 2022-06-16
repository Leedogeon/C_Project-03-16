// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemTypes.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


//착용한 장비가 없을때 사용할 내용들입니다.
USTRUCT(BlueprintType)
struct FDefaultEquipSetting
{
	GENERATED_BODY()
public:
	//헬맷없을때
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultHair_Full;
	//머리카락이 보여야 할 헬멧인 경우
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultHair_Half;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultFace;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultGlove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultShoes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* DefaultArmor;

	//무기 없는 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimBlueprint* DefaultAnimBlueprint;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FDefaultEquipSetting DefaultEquipSetting;

	/** 장비 정보를 저장할 공유포인터 변수입니다. */
	TSharedPtr<FItemInformation> HelmetInformation;
	TSharedPtr<FItemInformation> GloveInformation;
	TSharedPtr<FItemInformation> BeltInformation;
	TSharedPtr<FItemInformation> ShoesInformation;
	TSharedPtr<FItemInformation> ShoulderInformation;
	TSharedPtr<FItemInformation> ArmorInformation;

	TSharedPtr<FItemInformation> WeaponInformation;
	TSharedPtr<FItemInformation> ShieldInformation;
public:

	const TSharedPtr<FItemInformation>& GetHelmet() { return HelmetInformation; }
	void SetHelmet(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetGlove() { return GloveInformation; }
	void SetGlove(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetBelt() { return BeltInformation; }
	void SetBelt(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetShoes() { return ShoesInformation; }
	void SetShoes(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetShoulder() { return ShoulderInformation; }
	void SetShoulder(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetArmor() { return ArmorInformation; }
	void SetArmor(AItemActor* ItemActor);



	const TSharedPtr<FItemInformation>& GetWeapon() { return WeaponInformation; }
	void SetWeapon(AItemActor* ItemActor);

	const TSharedPtr<FItemInformation>& GetShield() { return ShieldInformation; }
	void SetShield(AItemActor* ItemActor);

	/**
	 * @brief 이미 장착중인 장비를 또 장착하려는지 확인합니다.
	 * @param ItemCode 장착하려는 아이템 코드
	 * @param Type 장착하려는 장비 타입
	 * @return 이미 장착한 아이템을 또 장착하려하면 참, 처음 장착하는 장비면 거짓.
	 */
	bool IsEquipped(const FName& ItemCode, const EEquipmentType Type);

	/**
	 * @brief 장비를 장착 해제합니다.
	 * @param ItemCode 장착 해제하려는 아이템 코드
	 * @param Type 장착 해제하려는 장비 타입
	 * @return 
	 */
	bool UnEquip(const FName& ItemCode, const EEquipmentType Type);

};
