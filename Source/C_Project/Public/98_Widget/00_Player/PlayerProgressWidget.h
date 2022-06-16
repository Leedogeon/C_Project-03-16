// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "98_Widget/00_Player/99_DragAndDrop/DragWidget.h"
#include "PlayerProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UPlayerProgressWidget : public UDragWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UProgressBar* ProgressBar_HP;
	UPROPERTY()
		class UProgressBar* ProgressBar_SP;

public:

	void UpdateProgressHP(class UStatusComponent* statsComp);
	void UpdateProgressSP(class UStatusComponent* statsComp);
};
