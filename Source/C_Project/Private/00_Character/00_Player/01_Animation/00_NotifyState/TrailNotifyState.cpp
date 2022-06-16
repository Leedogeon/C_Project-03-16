// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/01_Animation/00_NotifyState/TrailNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Components/ChildActorComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"
#include "particles/ParticleSystemComponent.h"

//변수로 빼면 좋은 것 -> SocketName, Width, ETrailWidthMode
//무기 TrailComponent의 BeginTrails 호출
void UTrailNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp!=nullptr)
	{
		auto Player = MeshComp->GetOwner<APlayerCharacter>();
		if (Player != nullptr) {
			auto Weapon = Player->GetWeapon();
			if (Weapon != nullptr)
			{
				Weapon->GetTrailComponent()->BeginTrails(StartSocketName,
					EndSocketName, TrailWidthMode, Width);

			}
		}
	}
}

//무기 TrailComponent의 EndTrails 호출
void UTrailNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp != nullptr)
	{
		auto Player = MeshComp->GetOwner<APlayerCharacter>();
		if (Player != nullptr) {
			auto Weapon = Player->GetWeapon();
			if (Weapon != nullptr)
			{
				Weapon->GetTrailComponent()->EndTrails();

			}
		}
	}
}
