// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/01_Consume/00_Potion/PotionActor.h"
#include "SPPotionActor.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API ASPPotionActor : public APotionActor
{
	GENERATED_BODY()
		virtual void InitItemInformation() override;
};
