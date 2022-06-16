// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/MainPlayerController.h"
#include "98_Widget/00_Player/MainWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/02_Component/LockOnComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AMainPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (MainWidgetObject != nullptr)
	{
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetObject);
		if (MainWidget != nullptr)
		{
			MainWidget->AddToViewport();

			APlayerCharacter* player = Cast<APlayerCharacter>(aPawn);
			if (player != nullptr)
			{
				player->OnChangedHP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateHPPercent);
				player->OnChangedSP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateSPPercent);

				player->OnChangedHP.Broadcast(player->GetStatusComponent());
				player->OnChangedSP.Broadcast(player->GetStatusComponent());


				player->GetLockOnComponent()->OnTargetLockOn.AddUniqueDynamic(this, &AMainPlayerController::OnTargetLockOnEvent);
				player->GetLockOnComponent()->OnLockOnWigetPosUpdate.AddUniqueDynamic(this, &AMainPlayerController::OnLockOnWigetPosUpdateEvent);
				player->GetLockOnComponent()->OnEndLockOn.AddUniqueDynamic(this, &AMainPlayerController::OnEndLockOnEvent);

				OnOpenInventory.AddUniqueDynamic(this, &AMainPlayerController::OnOpenInventoryEvent);
				OnOpenEquipment.AddUniqueDynamic(this, &AMainPlayerController::OnOpenEquipmentEvent);
			}
		}
	}

	if(LockOnWidgetObject!=nullptr)
	{
		LockOnWidget = CreateWidget<UUserWidget>(this, LockOnWidgetObject);
		if(LockOnWidget!=nullptr)
		{
			LockOnWidget->SetDesiredSizeInViewport(FVector2D(50, 50));
			LockOnWidget->SetVisibility(ESlateVisibility::Hidden);
			LockOnWidget->AddToViewport();
		}
	}


}

void AMainPlayerController::OnTargetLockOnEvent(AActor* Target)
{
	if (Target != nullptr) {

		FVector2D ScreenPos;
		if (ProjectWorldLocationToScreen(Target->GetActorLocation(), ScreenPos)) {

			LockOnWidget->SetPositionInViewport(ScreenPos);
			LockOnWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMainPlayerController::OnLockOnWigetPosUpdateEvent(AActor* Target)
{
	if (Target != nullptr) {

		FVector2D ScreenPos;
		if (ProjectWorldLocationToScreen(Target->GetActorLocation(), ScreenPos)) {
			ScreenPos.X -= (LockOnWidget->GetDesiredSize().X / 2);
			ScreenPos.Y -= (LockOnWidget->GetDesiredSize().Y / 2);
			LockOnWidget->SetPositionInViewport(ScreenPos);
		}
	}
}

void AMainPlayerController::OnEndLockOnEvent()
{
	if(LockOnWidget!=nullptr)
	{
		LockOnWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainPlayerController::OnOpenInventoryEvent()
{
	if(MainWidget != nullptr)
	{
		MainWidget->OpenInventory();
	}
}

void AMainPlayerController::OnOpenEquipmentEvent()
{
	if (MainWidget != nullptr)
	{
		MainWidget->OpenEquipment();
	}
}
