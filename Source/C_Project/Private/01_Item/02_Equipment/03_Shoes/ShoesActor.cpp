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
			//�����Ϸ��� �� ����� �̹� �������̾��� ����� ���
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::SHOES)) {
				if (EquipComp->GetShoes() != nullptr) {
					EquipComp->UnEquip(EquipComp->GetShoes()->Item_Code, EEquipmentType::SHOES);
				}
				//��� Mesh�� ��ü�ϰ�,
				Player->GetShoesMeshComponent()->SetSkeletalMesh(Equipment->ShoesMesh);
				//�� �ɷ�ġ�� �߰���.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//��� ������Ʈ�� ����
				EquipComp->SetShoes(this);

			}
		}
	}

	Destroy();
}
