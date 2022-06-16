// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/07_Weapon/WeaponActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"

void AWeaponActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FWeapon>();
		if (itemInfo != nullptr) {
			FWeapon* Info = new FWeapon(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}
}

void AWeaponActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);

	if(GenericItemInformation.P_ItemInfo.IsValid())
	{
		FWeapon* Equipment = (FWeapon*)GenericItemInformation.P_ItemInfo.Get();
		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto Weapon = Player->GetWeapon();
			auto EquipComp = Player->GetEquipmentComponent();
			if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::WEAPON))
			{
				if (EquipComp->GetWeapon() != nullptr) {
					Player->GetEquipmentComponent()->UnEquip(EquipComp->GetWeapon()->Item_Code, EEquipmentType::WEAPON);
				}

				Weapon->GetEquipmentMeshComponent()->SetStaticMesh(Equipment->WeaponMesh);
				Player->GetStatusComponent()->AddStatusValue(*Equipment);
				EquipComp->SetWeapon(this);

				Player->GetMesh()->SetAnimInstanceClass(Equipment->AnimBlueprint->GetAnimBlueprintGeneratedClass());
				Player->GetWeaponComponent()->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Equipment->SocketName);
			}

		}
	}

	Destroy();

}
