// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "01_Item/ItemTypes.h"

#include "StatusComponent.generated.h"


//캐릭터가 가지고 있을 능력치 정보 구조체입니다.
USTRUCT(BlueprintType)
struct FStatusValue
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float Damage;
	UPROPERTY(EditAnywhere)
		float Defence;
	UPROPERTY(EditAnywhere)
		float ActionSpeed = 1;

	UPROPERTY(EditAnywhere)
		int32 Str;
	UPROPERTY(EditAnywhere)
		int32 Dex;
	UPROPERTY(EditAnywhere)
		int32 Wiz;

	UPROPERTY(EditAnywhere)
		float HP = 100;
	UPROPERTY(EditAnywhere)
		float MaxHP = 100;
	UPROPERTY(EditAnywhere)
		float SP = 100;
	UPROPERTY(EditAnywhere)
		float MaxSP = 100;

	FStatusValue& operator+=(const FEquipment& Equipment)
	{
		Damage += Equipment.Damage;
		Defence += Equipment.Defence;
		ActionSpeed += Equipment.ActionSpeed;

		Str += Equipment.Str;
		Dex += Equipment.Dex;
		Wiz += Equipment.Wiz;

		MaxHP += Equipment.MaxHP;
		MaxSP += Equipment.MaxSP;
		//MaxMP += Equipment.MaxMP;

		return *this;
	}

	FStatusValue& operator-=(const FEquipment& Equipment)
	{
		Damage -= Equipment.Damage;
		Defence -= Equipment.Defence;
		ActionSpeed -= Equipment.ActionSpeed;

		Str -= Equipment.Str;
		Dex -= Equipment.Dex;
		Wiz -= Equipment.Wiz;

		MaxHP -= Equipment.MaxHP;
		MaxSP -= Equipment.MaxSP;
		//MaxMP -= Equipment.MaxMP;

		return *this;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	UPROPERTY(EditAnywhere)
		FStatusValue StatusValue;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	const FStatusValue& GetStatusValue() { return StatusValue; }

	//구조체로 바꾸기 전에 작성된 함수입니다. 필요하다면 GetStatusValue로 사용 가능합니다.
	float GetHP() { return StatusValue.HP; }
	float GetMaxHP() { return StatusValue.MaxHP; }
	float GetSP() { return StatusValue.SP; }
	float GetMaxSP() { return StatusValue.MaxSP; }

	/// <summary>
	/// Value만큼 SP값을 더합니다.
	///	음수값이 주어지면 줄어들게 됩니다.
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void AddSP(float Value);

	/**
	 * @brief Value값보다 SP가 많거나 같은지 확인합니다.
	 * @param Value 
	 * @return 많거나 같으면 참.
	 */
	bool CheckSP(float Value);

	/// <summary>
	/// Value만큼 HP값을 더합니다.
	///	음수값이 주어지면 줄어들게 됩니다.
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void AddHP(float Value);

	// Called every frame
	//틱마다 SP를 회복합니다.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//장비 구조체에서 받아온 능력치를 추가합니다.
	void AddStatusValue(const FEquipment& Equipment);
	//장비 구조체에서 받아온 능력치를 제거합니다.
	void RemoveStatusValue(const FEquipment& Equipment);
};
