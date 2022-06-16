// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Animation/01_Notify/SpawnActorNotify.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void USpawnActorNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr && ActorToSpawn != nullptr) {

		FActorSpawnParameters Param;
		Param.Owner = MeshComp->GetOwner();

		FVector SocketLocation = MeshComp->GetSocketLocation(SpawnSocketName);


		auto Actor = MeshComp->GetWorld()->SpawnActor<AActor>(ActorToSpawn, SocketLocation, FRotator::ZeroRotator, Param);

		if (bAttach) {
			Actor->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SpawnSocketName);
		}


	}
}
