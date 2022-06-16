// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "ConsumeActor.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API AConsumeActor : public AItemActor
{
	GENERATED_BODY()

public:
	virtual void ApplyItem_Implementation(AActor* Target) override;
};
