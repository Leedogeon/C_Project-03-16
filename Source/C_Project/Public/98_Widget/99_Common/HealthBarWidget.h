// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class UProgressBar* ProgressBar_HP;
public:

	void SetHPPercent(class UStatusComponent* statComp);
};
