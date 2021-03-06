// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/03_Shoes/ShoesActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void AShoesActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FShoes>();
		if (itemInfo != nullptr) {
			FShoes* Info = new FShoes(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}

}

void AShoesActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);
	if (GenericItemInformation.P_ItemInfo.IsValid())
	{
		FShoes* Equipment = (FShoes*)GenericItemInformation.P_ItemInfo.Get();

		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();
			//장착하려는 이 헬맷이 이미 장착중이었던 헬맷인 경우
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::SHOES)) {
				if (EquipComp->GetShoes() != nullptr) {
					EquipComp->UnEquip(EquipComp->GetShoes()->Item_Code, EEquipmentType::SHOES);
				}
				//헬맷 Mesh를 교체하고,
				Player->GetShoesMeshComponent()->SetSkeletalMesh(Equipment->ShoesMesh);
				//새 능력치를 추가함.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//장비 컴포넌트에 저장
				EquipComp->SetShoes(this);

			}
		}
	}

	Destroy();
}
