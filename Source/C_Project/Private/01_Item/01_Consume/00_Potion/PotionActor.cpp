// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Consume/00_Potion/PotionActor.h"
#include "00_Character/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"



void APotionActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		FPotion* Potion = new FPotion(*GetItemInformation<FPotion>());
		GenericItemInformation.P_ItemInfo = MakeShareable(Potion);

		if (GenericItemInformation.P_ItemInfo.IsValid()) {
			Potion = (FPotion*)GenericItemInformation.P_ItemInfo.Get();
		}
	}

}

void APotionActor::Recovery(ABaseCharacter* Target)
{
	if (GenericItemInformation.P_ItemInfo.IsValid()) {
		FPotion* Potion = (FPotion*)GenericItemInformation.P_ItemInfo.Get();
		if (Potion != nullptr) {

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Potion->UseParticle, Target->GetActorLocation());
			UGameplayStatics::SpawnSoundAtLocation(this, Potion->UseSound, Target->GetActorLocation());

			Target->GetStatusComponent()->AddHP(Potion->RecoverHP);
			//Target->GetStatusComponent()->AddMP(Potion->RecoverMP);
			Target->GetStatusComponent()->AddSP(Potion->RecoverSP);
		}
	}

	Destroy();
}

void APotionActor::ApplyItem_Implementation(AActor* Target)
{
	if (Target != nullptr)
	{

		if (GenericItemInformation.P_ItemInfo.IsValid()) {
			FPotion* Potion = (FPotion*)GenericItemInformation.P_ItemInfo.Get();
			if (Potion != nullptr)
			{
				auto Character = Cast<ABaseCharacter>(Target);
				if (Character != nullptr)
				{
					if(Character->OnApplyPotionEffect.IsBound())
					{
						Destroy();
					}

					if (Character->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false)
					{
						Super::ApplyItem_Implementation(Target);
						Character->OnApplyPotionEffect.AddUniqueDynamic(this, &APotionActor::Recovery);
						Character->GetMesh()->GetAnimInstance()->Montage_Play(Potion->UseMontage);
					}else
					{
						Destroy();
					}
				}
			}
		}
		
	}

}
