// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "EquipmentActor.generated.h"

/**
 * 모든 장비의 부모입니다.
 * 공통적인 기능이 필요하다면 추가하세요.
 */
UCLASS()
class C_PROJECT_API AEquipmentActor : public AItemActor
{
	GENERATED_BODY()
	
};
