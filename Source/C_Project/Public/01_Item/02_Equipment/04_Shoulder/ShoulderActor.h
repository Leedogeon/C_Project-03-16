// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/02_Equipment/EquipmentActor.h"
#include "ShoulderActor.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API AShoulderActor : public AEquipmentActor
{
	GENERATED_BODY()
		virtual void InitItemInformation() override;
	virtual void ApplyItem_Implementation(AActor* Target) override;
};
