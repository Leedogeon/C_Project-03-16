// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/07_Weapon/00_TwoHanded/TwoHandedActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/00_Equipable/Equipment_Spawn.h"

void ATwoHandedActor::ApplyItem_Implementation(AActor* Target)
{
	auto Player = Cast<APlayerCharacter>(Target);
	if (Player != nullptr)
	{

		auto EquipComp = Player->GetEquipmentComponent();

		auto EquippedShield = EquipComp->GetShield();
		if (EquippedShield.IsValid()) {
			Player->GetEquipmentComponent()->UnEquip(EquippedShield->Item_Code, EEquipmentType::SHIELD);
		}
			auto Shield = Player->GetShield();
			Shield->GetEquipmentMeshComponent()->SetStaticMesh(nullptr);
			EquipComp->SetShield(nullptr);


			Super::ApplyItem_Implementation(Target);
	}
}
