// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "AttackNotifyState.generated.h"

/**
 *	틱마다 무기에 트레이스를 그려 걸린 대상에게 피해를 줍니다.
 *	-> 무기의 콜리전 오버렙을 이용하여 좀 더 정확하게 판정하는 방식으로 수정되었습니다.
 */
UCLASS()
class C_PROJECT_API UAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class ABaseCharacter* Owner;

	UPROPERTY(EditAnywhere)
		FName StartSocket;
	UPROPERTY(EditAnywhere)
		FName EndSocket;
	UPROPERTY(EditAnywhere)
		float Radius;

	//트레이스로 거를 오브젝트 타입
	UPROPERTY(EditAnywhere)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
