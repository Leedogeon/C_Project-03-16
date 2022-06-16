// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/01_Consume/ConsumeActor.h"
#include "PotionActor.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API APotionActor : public AConsumeActor
{
	GENERATED_BODY()


	UFUNCTION()
		void Recovery(class ABaseCharacter* Target);
protected:
	virtual void InitItemInformation() override;
public:
	virtual void ApplyItem_Implementation(AActor* Target) override;
};
