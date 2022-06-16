// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Widget/99_Common/DamageTextWidget.h"
#include "Components/TextBlock.h"

void UDamageTextWidget::SetDamageText(const float Damage)
{
	TextBlock_Damage->SetText(FText::AsNumber(Damage));
}
