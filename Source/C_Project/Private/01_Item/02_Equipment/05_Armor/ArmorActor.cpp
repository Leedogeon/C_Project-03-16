// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/05_Armor/ArmorActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"
void AArmorActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FArmor>();
		if (itemInfo != nullptr) {
			FArmor* Info = new FArmor(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}
}

void AArmorActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);

	if (GenericItemInformation.P_ItemInfo.IsValid())
	{
		FArmor* Equipment = (FArmor*)GenericItemInformation.P_ItemInfo.Get();

		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();
			//이미 장착중이었던경우
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::ARMOR)) {

				if (EquipComp->GetArmor() != nullptr) {
					//이전에 장착했던 장비 정보가 있다면, 그 장비의 능력치를 제거합니다.
					Player->GetEquipmentComponent()->UnEquip(EquipComp->GetArmor()->Item_Code, EEquipmentType::ARMOR);
				}
				//Mesh를 교체하고,
				Player->GetMesh()->SetSkeletalMesh(Equipment->ArmorMesh);
				//새 능력치를 추가함.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//장비 컴포넌트에 저장
				EquipComp->SetArmor(this);

			}
		}
	}

	Destroy();
}
