// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/00_Player/PlayerProgressWidget.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Components/ProgressBar.h"

void UPlayerProgressWidget::UpdateProgressHP(UStatusComponent* statsComp)
{
	float per = statsComp->GetHP() / statsComp->GetMaxHP();
	ProgressBar_HP->SetPercent(per);
}

void UPlayerProgressWidget::UpdateProgressSP(UStatusComponent* statsComp)
{
	float per = statsComp->GetSP() / statsComp->GetMaxSP();
	ProgressBar_SP->SetPercent(per);
}
