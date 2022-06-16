// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetLockOn, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockOnWigetPosUpdate, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndLockOn);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

	//타겟을 락온했을때 호출되는 이밴트입니다.
	UPROPERTY(BlueprintAssignable)
		FOnTargetLockOn OnTargetLockOn;
	//타겟에게 락온 위젯을 계속 이동시키는 델리게이트 변수입니다.
	UPROPERTY(BlueprintAssignable)
		FOnLockOnWigetPosUpdate OnLockOnWigetPosUpdate;
	//락온이 끝나면 사용됩니다.
	UPROPERTY(BlueprintAssignable)
		FOnEndLockOn OnEndLockOn;
protected:

	//락온이 끝나면 Broadcast로 호출됩니다.
	UFUNCTION()
		void OnEndLockOnEvent();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		class APlayerCharacter* Player;
	UPROPERTY()
		class UCameraComponent* CameraComponent;

	//락온 가능한 대상들을 저장할 배열업니다. 실시간 정렬
	UPROPERTY()
		TArray<AActor*> LockOnableActors_Sort;
	//락온 가능한 대상들을 저장할 배열업니다. 정렬x
	UPROPERTY()
		TArray<AActor*> LockOnableActors;


	//이 거리보다 멀어지면 락온 가능한 액터 배열에서 제거합니다.
	UPROPERTY(EditAnywhere)
		float LockOnDistance;
	//락온 대상을 탐지하기 위한 트레이스의 반지름입니다.
	UPROPERTY(EditAnywhere)
		float Radius;


	UPROPERTY()
		AActor* LockOnTarget;

	/**
	 * @brief 카메라로 부터 락온 대상을 가져올 트레이스를 그립니다.
	 */
	void CreateCameraTrace();
	/**
	 * @brief 대상이 플레이어와 너무 멀어지면 락온 대상에서 제외합니다.
	 */
	UFUNCTION(BlueprintCallable)
	void SortLockOnableActors();
	/**
	 * @brief 카메라가 타겟을 바라보게 합니다.
	 */
	void CameraLookAtTarget();


	/**
	 * @brief 락온 대상들을 배열에서 비웁니다.
	 */
	void ClearLockOnActors();
public:

	AActor* GetLockOnTarget() { return LockOnTarget; }

	/**
	 * @brief 락온 타겟을 변경합니다.
	 */
	void SetNextLockOnTarget();
	void SetPreLockOnTarget();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
