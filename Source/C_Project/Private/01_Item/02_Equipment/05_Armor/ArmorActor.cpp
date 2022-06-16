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
			//�̹� �������̾������
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::ARMOR)) {

				if (EquipComp->GetArmor() != nullptr) {
					//������ �����ߴ� ��� ������ �ִٸ�, �� ����� �ɷ�ġ�� �����մϴ�.
					Player->GetEquipmentComponent()->UnEquip(EquipComp->GetArmor()->Item_Code, EEquipmentType::ARMOR);
				}
				//Mesh�� ��ü�ϰ�,
				Player->GetMesh()->SetSkeletalMesh(Equipment->ArmorMesh);
				//�� �ɷ�ġ�� �߰���.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//��� ������Ʈ�� ����
				EquipComp->SetArmor(this);

			}
		}
	}

	Destroy();
}
