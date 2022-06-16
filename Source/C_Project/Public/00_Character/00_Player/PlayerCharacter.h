// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "C_Project/C_Project.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStatusValue, class UStatusComponent*, StatComp);

UCLASS()
class C_PROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	/** 캐릭터 파츠(얼굴,몸통 ETC...) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* GloveMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* BeltMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* FaceMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* HairMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* HelmetMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* ShoesMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* ShoulderMeshComponent;

	//무기와 방패를 저장할 ChildActorComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UChildActorComponent* WeaponActorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UChildActorComponent* ShieldActorComponent;

	//락온기능을 정의한 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class ULockOnComponent* LockOnComponent;
	//아이템 정보를 저장하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UInventoryComponent* InventoryComponent;

	//장비창에 캐릭터를 표시하기 위한 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneCaptureComponent2D* SceneCapture2DComponent;
public:

	PROPERTY_GETTER(SceneCapture2DComponent, USceneCaptureComponent2D*);

	PROPERTY_GETTER(HelmetMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(GloveMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(BeltMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(FaceMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(HairMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(ShoesMeshComponent, USkeletalMeshComponent*);
	PROPERTY_GETTER(ShoulderMeshComponent, USkeletalMeshComponent*);

	PROPERTY_GETTER(InventoryComponent, UInventoryComponent*);

	//매크로로 정의되지 않은 Get, Set함수는 매크로 정의 이전에 작성된 함수입니다.
	class ULockOnComponent* GetLockOnComponent() { return LockOnComponent; }


	UChildActorComponent* GetWeaponComponent() { return WeaponActorComponent; }
	PROPERTY_GETTER(ShieldActorComponent, UChildActorComponent*);

	/**
	 * @brief ChildActorComponent에 할당된 무기액터를 가져옵니다.
	 * 비어있는경우 생성해서 할당 후 가져옵니다.
	 * @return ChildActorComponent에 할당된 무기액터
	 */
	class AWeapon_Spawn* GetWeapon();

	/**
	 * @brief ChildActorComponent에 할당된 방패액터를 가져옵니다.
	 * 비어있는경우 생성해서 할당 후 가져옵니다.
	 * @return ChildActorComponent에 할당된 방패액터
	 */
	class AEquipment_Spawn* GetShield();

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/**
	 * @brief 마우스 좌 우 입력에 이 함수가 호출됩니다.
	 * @param Val 
	 */
	virtual void AddControllerYawInput(float Val) override;


	/**
	 * @brief 락온시 타겟을 바꾸는데 약간의 딜래이를 주기 위한 타이머 핸들입니다.
	 */
	FTimerHandle NextLockOnTimerHandle;
	FTimerHandle PreLockOnTimerHandle;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** 입력 바인딩을 위한 함수 목록입니다. */
	void Run();
	void StopRun();

	void Roll();

	//이 부울변수로 다음 공격이 이어질지 확인합니다.
	bool bPressAttack = false;
	void Attack();
	void StopAttack();

	void PickUp();

	void OpenInventory();
	void OpenEquipment();

	bool bLockOn = false;
	void LockOn();

	virtual void Jump() override;


	void PressQuick01();
	void PressQuick02();
	void PressQuick03();
	void PressQuick04();
	void PressQuick05();

	//공격시 락온중이라면, 락온대상을 향하게 합니다.
	void LookAtLockOnTarget();

	//캐릭터의 행동 상태를 변경합니다.
	virtual void SetActionState(EActionState newState) override;
protected:

	virtual void PostInitializeComponents() override;


	UFUNCTION()
		void OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	//아이템을 줏으면 재생되는 사운드
	UPROPERTY(EditAnywhere)
		class USoundBase* PickUpItemSound;

public:

	//플레이어의 상태정보가 변하면 호출되는 델리게이트.
	UPROPERTY(BlueprintAssignable)
		FOnChangeStatusValue OnChangeStatusValue;
};



