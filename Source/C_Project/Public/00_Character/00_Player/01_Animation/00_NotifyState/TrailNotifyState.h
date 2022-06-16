// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TrailNotifyState.generated.h"

/**
 *	무기에 Trail을 적용합니다.
 */
UCLASS()
class C_PROJECT_API UTrailNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	//Trail의 시작 위치에 해당하는 소켓 이름입니다.
	UPROPERTY(EditAnywhere)
		FName StartSocketName;
	//Trail의 끝 위치에 해당하는 소켓 이름입니다.
	UPROPERTY(EditAnywhere)
		FName EndSocketName;

	//Trail 모드에 관련된 변수입니다.
	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETrailWidthMode> TrailWidthMode;
	//생성될 Trail의 넓이입니다.
	UPROPERTY(EditAnywhere)
		float Width;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
