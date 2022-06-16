// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UTextBlock* TextBlock_Damage;
public:
	void SetDamageText(const float Damage);
};
