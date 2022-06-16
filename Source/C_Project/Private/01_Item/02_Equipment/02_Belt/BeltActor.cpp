// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/02_Belt/BeltActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void ABeltActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FBelt>();
		if (itemInfo != nullptr) {
			FBelt* Info = new FBelt(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}

}

void ABeltActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);

	if (GenericItemInformation.P_ItemInfo.IsValid())
	{
		FBelt* Equipment = (FBelt*)GenericItemInformation.P_ItemInfo.Get();

		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();
			//장착하려는 이 헬맷이 이미 장착중이었던 헬맷인 경우
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::BELT)) {

				if (EquipComp->GetBelt() != nullptr) {
					EquipComp->UnEquip(EquipComp->GetBelt()->Item_Code, EEquipmentType::BELT);
				}
				//헬맷 Mesh를 교체하고,
				Player->GetBeltMeshComponent()->SetSkeletalMesh(Equipment->BeltMesh);
				//새 능력치를 추가함.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//장비 컴포넌트에 저장
				EquipComp->SetBelt(this);

			}
		}
	}

	Destroy();
}
