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
			//�����Ϸ��� �� ����� �̹� �������̾��� ����� ���
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::GLOVE)) {

				if (EquipComp->GetGlove() != nullptr) {
					//������ �����ߴ� ��� ������ �ִٸ�, �� ����� �ɷ�ġ�� �����մϴ�.
					EquipComp->UnEquip(EquipComp->GetGlove()->Item_Code, EEquipmentType::GLOVE);
				}
				//��� Mesh�� ��ü�ϰ�,
				Player->GetGloveMeshComponent()->SetSkeletalMesh(Equipment->GloveMesh);
				//�� �ɷ�ġ�� �߰���.
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				//��� ������Ʈ�� ����
				EquipComp->SetGlove(this);

			}
		}
	}

	Destroy();
}
