// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/00_Helmet/HelmetActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void AHelmetActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto info = GetItemInformation<FHelmet>();
		if (info != nullptr) {
			FHelmet* Helmet = new FHelmet(*info);
			GenericItemInformation.P_ItemInfo = MakeShareable(Helmet);
		}
	}
}

void AHelmetActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);
	if(GenericItemInformation.P_ItemInfo.IsValid())
	{
		FHelmet* Helmet = (FHelmet*)GenericItemInformation.P_ItemInfo.Get();
		//Helmet->HelmetMesh;
		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();

			//장착하려는 이 헬맷이 이미 장착중이었던 헬맷인 경우
			if (!EquipComp->IsEquipped(Helmet->Item_Code,EEquipmentType::HELMET)) {

				if (EquipComp->GetHelmet() != nullptr) {
					//이전에 장착했던 헬맷 정보가 있다면, 그 헬맷의 능력치를 제거합니다.
					EquipComp->UnEquip(EquipComp->GetHelmet()->Item_Code, EEquipmentType::HELMET);
				}
				//헬맷 Mesh를 교체하고,
				Player->GetHelmetMeshComponent()->SetSkeletalMesh(Helmet->HelmetMesh);
				//새 능력치를 추가함.
				Player->GetStatusComponent()->AddStatusValue(*Helmet);
				//장비 컴포넌트에 저장
				EquipComp->SetHelmet(this);

			}
		}
	}

	Destroy();

}

