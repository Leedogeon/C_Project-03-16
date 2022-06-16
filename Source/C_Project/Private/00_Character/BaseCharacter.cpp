// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/BaseCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "98_Widget/99_Common/DamageTextWidget.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
					  //생성자에서만 사용 가능
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);

	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(150,15));
	HealthBarWidgetComponent->SetVisibility(false);

	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	
	FHitResult Hit;
	FVector OutImpulseDir;
	DamageEvent.GetBestHitInfo(this, DamageCauser, Hit, OutImpulseDir);

	if(DamageTextWidgetComponentObject!=nullptr)
	{

		UWidgetComponent* widgetComp = NewObject<UWidgetComponent>(this, DamageTextWidgetComponentObject);
		if(widgetComp!=nullptr)
		{
			//컴포넌트 동적생성시 반드시 호출.
			widgetComp->RegisterComponent();
			widgetComp->SetWorldLocation(Hit.Location);

			//위젯 컴포넌트 내부 유저 위젯을 가져와서, 텍스트를 피해량으로 설정.
			UDamageTextWidget* widget =	Cast<UDamageTextWidget>(widgetComp->GetUserWidgetObject());
			if(widget != nullptr)
			{
				widget->SetDamageText(DamageAmount);
			}
		}
	}


	//1. DamageAmount만큼 체력을 깎음.
	StatusComponent->AddHP((-1) * DamageAmount);
	//2. 남은 체력을 로그로 찍음.
	UE_LOG(LogTemp, Log, TEXT("HP : %f"), StatusComponent->GetHP());




	HealthBarWidgetComponent->SetVisibility(true);

	//타이머 돌리기 전에 기존 타이머가 있으면, 멈추고 다시 돌리자.
	if (GetWorldTimerManager().TimerExists(HealthBarWidgetVisibleTimerHandle)) {
		GetWorldTimerManager().ClearTimer(HealthBarWidgetVisibleTimerHandle);
	}

	FTimerDelegate VisibleTimerDel = FTimerDelegate::CreateUObject(
		HealthBarWidgetComponent,
		&UWidgetComponent::SetVisibility, false, false);
	GetWorldTimerManager().SetTimer(HealthBarWidgetVisibleTimerHandle, VisibleTimerDel, 3.f, false);



	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


