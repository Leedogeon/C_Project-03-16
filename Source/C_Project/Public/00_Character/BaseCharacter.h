// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Project/C_Project.h"
#include "BaseCharacter.generated.h"

//체력이 변하면 사용되는 델리게이트 정의입니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
//스테미너가 변하면 사용되는 델리게이트 정의입니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedSP, class UStatusComponent*, statComp);

//물약류 아이템을 사용 시 물약 효과 타이밍에 사용되는 델리게이트 정의입니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnApplyPotionEffect, class ABaseCharacter*, Target);

//캐릭터 상태를 정의하는 Enum 
UENUM(BlueprintType)
enum class EActionState : uint8
{
	NORMAL,
	RUN,
	ROLL,
	ATTACK,
	JUMP
};

UCLASS()
class C_PROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//캐릭터의 체력상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
		FOnChangedHP OnChangedHP;
	//캐릭터의 스테미너 상황이 변하면 실행되는 델리게이트
	UPROPERTY(BlueprintAssignable)
		FOnChangedSP OnChangedSP;
	//물약 사용시 플레이중인 애니메이션 특정 포인트에서 효과를 주고 싶을 때 사용됩니다.
	UPROPERTY(BlueprintAssignable)
		FOnApplyPotionEffect OnApplyPotionEffect;

protected:

	//델리게이트에 저장할 함수는 반드시 UFUNCTION 매크로 붙일 것.
	UFUNCTION()
		virtual void OnChangedHPEvent(class UStatusComponent* statComp){ }
	UFUNCTION()
		virtual void OnChangedSPEvent(class UStatusComponent* statComp) { }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//착용중인 장비 아이템을 기억하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEquipmentComponent* EquipmentComponent;

	//캐릭터의 상태정보를 기억하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStatusComponent* StatusComponent;

	//캐릭터 머리위에 체력표시줄을 띄우기 위한 위젯 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UWidgetComponent* HealthBarWidgetComponent;

	//TSubclassOf : 특정 클래스를 상속받은 오브젝트만 가져올 수 있음.
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetComponent> DamageTextWidgetComponentObject;

	//현 캐릭터 상태를 정의하는 열거형 변수
	UPROPERTY(BlueprintReadOnly)
		EActionState ActionState;

	virtual void SetActionState(EActionState newState){ }
public:

	PROPERTY_GETTER(ActionState, EActionState);
	PROPERTY_GETTER(EquipmentComponent, UEquipmentComponent*);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStatusComponent* GetStatusComponent() { return StatusComponent; }

	/**
	 * @brief 
	 * @param DamageAmount 피해량
	 * @param DamageEvent 피해에 대한 필요한 정보를 저장하는 구조체
	 * @param EventInstigator 이 대상에게 피해를 준 컨트롤러
	 * @param DamageCauser 어느 물체에 의해서 피해를 입었는가?
	 * @return 최종피해량
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	//피해를 입었을 때 보여지는 체력표시줄을 N초 후 숨기기 위한 타이머 핸들
	UPROPERTY()
		FTimerHandle HealthBarWidgetVisibleTimerHandle;


};
