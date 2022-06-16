// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/Monster.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "98_Widget/99_Common/HealthBarWidget.h"

AMonster::AMonster()
{
	GetCapsuleComponent()->SetCollisionProfileName("MonsterPreset");
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnChangedHP.AddUniqueDynamic(this, &AMonster::OnChangedHPEvent);
	HealthBarWidgetComponent->InitWidget();
	OnChangedHP.Broadcast(StatusComponent);
}

void AMonster::OnChangedHPEvent(UStatusComponent* statComp)
{
	UUserWidget* widget =  HealthBarWidgetComponent->GetUserWidgetObject();
	if(widget!=nullptr)
	{
		UHealthBarWidget* HpWidget = Cast<UHealthBarWidget>(widget);
		if(HpWidget!=nullptr)
		{
			HpWidget->SetHPPercent(statComp);
		}
	}
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	//OnChangedHP.Broadcast(StatusComponent);
}
