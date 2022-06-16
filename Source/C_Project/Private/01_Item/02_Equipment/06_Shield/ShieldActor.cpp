// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Equipment/06_Shield/ShieldActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/00_Equipable/Equipment_Spawn.h"
#include "Kismet/KismetSystemLibrary.h"

void AShieldActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid() == false) {
		auto itemInfo = GetItemInformation<FShield>();
		if (itemInfo != nullptr) {
			FShield* Info = new FShield(*itemInfo);
			GenericItemInformation.P_ItemInfo = MakeShareable(Info);
		}
	}
}

void AShieldActor::ApplyItem_Implementation(AActor* Target)
{
	Super::ApplyItem_Implementation(Target);
	if(GenericItemInformation.P_ItemInfo.IsValid())
	{

		FShield* Equipment = (FShield*)GenericItemInformation.P_ItemInfo.Get();
		auto Player = Cast<APlayerCharacter>(Target);
		if (Player != nullptr)
		{
			auto Shield = Player->GetShield();
			auto EquipComp = Player->GetEquipmentComponent();

			if (!
				(EquipComp->GetWeapon().IsValid() 
				&& ((FWeapon*)EquipComp->GetWeapon().Get())->WeaponType == EWeaponType::TWO_HANDED_SWORD)) {

				if (!EquipComp->IsEquipped(Equipment->Item_Code, EEquipmentType::SHIELD))
				{

					if (EquipComp->GetShield() != nullptr) {
						Player->GetEquipmentComponent()->UnEquip(EquipComp->GetShield()->Item_Code, EEquipmentType::SHIELD);
					}

					Player->GetShieldActorComponent()->
						AttachToComponent(Player->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), Equipment->SocketName);

					Shield->GetEquipmentMeshComponent()->SetStaticMesh(Equipment->ShieldMesh);
					Player->GetStatusComponent()->AddStatusValue(*Equipment);
					EquipComp->SetShield(this);
				}
			}else
			{
				UE_LOG(LogTemp, Warning, TEXT("양손무기를 장착중임."));
			}
		}
	}



	Destroy();
}
