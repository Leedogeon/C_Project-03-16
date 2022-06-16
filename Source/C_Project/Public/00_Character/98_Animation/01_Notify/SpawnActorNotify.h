// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnActorNotify.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API USpawnActorNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere)
		FName SpawnSocketName;
	UPROPERTY(EditAnywhere)
		bool bAttach = false;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
