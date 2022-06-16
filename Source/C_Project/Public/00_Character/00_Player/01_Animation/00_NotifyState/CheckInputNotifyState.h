// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CheckInputNotifyState.generated.h"

/**
 * 구간동안 플레이어의 공격 입력이 또 들어왔는지 확인합니다.
 * 입력이 들어오지 않았다면, 재생중인 몽타주를 멈춥니다.
 */
UCLASS()
class UCheckInputNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	UCheckInputNotifyState();

	UPROPERTY()
		class APlayerCharacter* Player;
	//틱중에 공격입력이 들어오면, 공격을 계속한다고 생각합니다.
	UPROPERTY()
		bool bContinue = false;
	/*
	 *	FString
	 *	FName	-	검색용(대소문자 구분 안 함)
	 *	FText	-	UI전용
	 */
	//bContinue가 참이 되면 이 Section으로 점프합니다.
	UPROPERTY(EditAnywhere)
		FName NextSection;

	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
