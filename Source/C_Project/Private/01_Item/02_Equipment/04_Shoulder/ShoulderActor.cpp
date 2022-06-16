// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/04_Shoulder/ShoulderActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void AShoulderActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FShoulder>();
		if (itemInfo != nullptr) {
			FShoulder* Info = new FShoulder(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}
}

void AShoulderActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);

	if (GenericItemInformation.P_ItemInfo.IsValid())
	{
		FShoulder* Equipment = (FShoulder*)GenericItemInformation.P_ItemInfo.Get();

		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto EquipComp = Player->GetEquipmentComponent();
			//�����Ϸ��� �� ����� �̹� �������̾��� ����� ���
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::SHOULDER)) {

				if (EquipComp->GetShoulder() != nullptr) {
					//������ �����ߴ� ��� ������ �ִٸ�, �� ����� �ɷ�ġ�� �����մϴ�.
					EquipComp->UnEquip(EquipComp->GetShoulder()->Item_Code, EEquipmentType::SHOULDER);
				}
				//��� Mesh�� ��ü�ϰ�,
				Player->GetShoulderMeshComponent()->SetSkeletalMesh(Equipment->ShoulderMesh);
				//�� �ɷ�ġ�� �߰���.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//��� ������Ʈ�� ����
				EquipComp->SetShoulder(this);

			}
		}
	}

	Destroy();
}
