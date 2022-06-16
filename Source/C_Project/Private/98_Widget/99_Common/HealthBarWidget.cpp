// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/99_Common/HealthBarWidget.h"

#include "00_Character/99_Component/StatusComponent.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHPPercent(UStatusComponent* statComp)
{
	float p = statComp->GetHP() / statComp->GetMaxHP();
	ProgressBar_HP->SetPercent(p);
}
