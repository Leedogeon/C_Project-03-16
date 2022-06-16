// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/01_Glove/GloveActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void AGloveActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FGlove>();
		if (itemInfo != nullptr) {
			FGlove* Info = new FGlove(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}
}

void AGloveActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);
	if (GenericItemInformation.P_ItemInfo.IsValid())
	{
		FGlove* Equipment = (FGlove*)GenericItemInformation.P_ItemInfo.Get();

		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();
			//장착하려는 이 헬맷이 이미 장착중이었던 헬맷인 경우
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::GLOVE)) {

				if (EquipComp->GetGlove() != nullptr) {
					//이전에 장착했던 장비 정보가 있다면, 그 장비의 능력치를 제거합니다.
					EquipComp->UnEquip(EquipComp->GetGlove()->Item_Code, EEquipmentType::GLOVE);
				}
				//헬맷 Mesh를 교체하고,
				Player->GetGloveMeshComponent()->SetSkeletalMesh(Equipment->GloveMesh);
				//새 능력치를 추가함.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//장비 컴포넌트에 저장
				EquipComp->SetGlove(this);

			}
		}
	}

	Destroy();
}
