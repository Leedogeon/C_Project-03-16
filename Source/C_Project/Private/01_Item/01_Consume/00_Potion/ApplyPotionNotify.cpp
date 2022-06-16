// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Consume/00_Potion/ApplyPotionNotify.h"
#include "00_Character/BaseCharacter.h"
void UApplyPotionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if(MeshComp!=nullptr)
	{
		auto Character = MeshComp->GetOwner<ABaseCharacter>();
		if(Character!=nullptr)
		{
			Character->OnApplyPotionEffect.Broadcast(Character);
			Character->OnApplyPotionEffect.Clear();
		}
	}
}
