// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/02_Equipment/07_Weapon/WeaponActor.h"
#include "TwoHandedActor.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API ATwoHandedActor : public AWeaponActor
{
	GENERATED_BODY()


		virtual void ApplyItem_Implementation(AActor* Target) override;
};
