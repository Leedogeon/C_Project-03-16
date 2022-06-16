// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Animation/00_NotifyState/AttackNotifyState.h"

#include "Components/SkeletalMeshComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ChildActorComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Owner = MeshComp->GetOwner<ABaseCharacter>();
	if(Owner!=nullptr)
	{
		if(Owner->IsA<APlayerCharacter>())
		{
			auto Weapon = Cast<APlayerCharacter>(Owner)->GetWeapon();
			Weapon->SetActorEnableCollision(true);
		}
	}
}

void UAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	/*
	if (Owner != nullptr) {

		if(Owner->IsA<APlayerCharacter>())
		{
			auto player = Cast<APlayerCharacter>(Owner);
			AActor* childActor =  player->GetWeaponComponent()->GetChildActor();
			if(childActor!=nullptr)
			{
				AWeapon_Spawn* weapon = Cast<AWeapon_Spawn>(childActor);
				if(weapon!=nullptr)
				{
					FVector StartLocation = weapon->GetEquipmentMeshComponent()->GetSocketLocation(StartSocket);
					FVector EndLocation = weapon->GetEquipmentMeshComponent()->GetSocketLocation(EndSocket);
					
					TArray<FHitResult> Hits;

					if(UKismetSystemLibrary::SphereTraceMultiForObjects(Owner,
						StartLocation,
						EndLocation,
						Radius,
						ObjectTypes,
						false,
						TArray<AActor*>(),
						EDrawDebugTrace::ForOneFrame,
						Hits, true))
					{

						for(FHitResult Hit : Hits)
						{
							if (weapon->IsAlreadyHitActor(Hit.GetActor()) == false) {
								weapon->AddUniqueHitActor(Hit.GetActor());
								UE_LOG(LogTemp, Log, TEXT("Hit : %s"), *Hit.GetActor()->GetName());


								Hit.GetActor()->TakeDamage(10.f, FDamageEvent(), nullptr, nullptr);
								UNiagaraFunctionLibrary::SpawnSystemAtLocation(player, player->HitParticle, Hit.Location);
							}
						}

					}

				}
			}
		}


	}
	*/
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(Owner!=nullptr)
	{
		if(Owner->IsA<APlayerCharacter>())
		{
			Cast<APlayerCharacter>(Owner)->GetWeapon()->ClearHitActors();
			Cast<APlayerCharacter>(Owner)->GetWeapon()->SetActorEnableCollision(false);
		}
	}
}
