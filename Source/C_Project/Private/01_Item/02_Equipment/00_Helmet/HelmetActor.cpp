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

			//�����Ϸ��� �� ����� �̹� �������̾��� ����� ���
			if (!EquipComp->IsEquipped(Helmet->Item_Code,EEquipmentType::HELMET)) {

				if (EquipComp->GetHelmet() != nullptr) {
					//������ �����ߴ� ��� ������ �ִٸ�, �� ����� �ɷ�ġ�� �����մϴ�.
					EquipComp->UnEquip(EquipComp->GetHelmet()->Item_Code, EEquipmentType::HELMET);
				}
				//��� Mesh�� ��ü�ϰ�,
				Player->GetHelmetMeshComponent()->SetSkeletalMesh(Helmet->HelmetMesh);
				//�� �ɷ�ġ�� �߰���.
				Player->GetStatusComponent()->AddStatusValue(*Helmet);
				//��� ������Ʈ�� ����
				EquipComp->SetHelmet(this);

			}
		}
	}

	Destroy();

}

