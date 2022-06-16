// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootStepNotify.generated.h"

/**
 *	머터리얼 표면 타입을 읽어와 표면마다 다른 발자국과 사운드를 생성합니다.
 */
UCLASS()
class C_PROJECT_API UFootStepNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere)
		class USoundBase* FootStepSound;


	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* DefaultParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* GroundParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* GrassParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* GravalParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* IceParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* SnowParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* WaterParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* WoodParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* SandParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* DirtParticle;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* MetalParticle;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
