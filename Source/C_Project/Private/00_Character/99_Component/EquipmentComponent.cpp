// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/EquipmentComponent.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentComponent::SetHelmet(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		HelmetInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}else
	{
		HelmetInformation = nullptr;
	}
}

void UEquipmentComponent::SetGlove(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		GloveInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		GloveInformation = nullptr;
	}
}

void UEquipmentComponent::SetBelt(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		BeltInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		BeltInformation = nullptr;
	}
}

void UEquipmentComponent::SetShoes(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		ShoesInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		ShoesInformation = nullptr;
	}
}

void UEquipmentComponent::SetShoulder(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		ShoulderInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		ShoulderInformation = nullptr;
	}
}

void UEquipmentComponent::SetArmor(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		ArmorInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		ArmorInformation = nullptr;
	}
}

void UEquipmentComponent::SetWeapon(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		WeaponInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		WeaponInformation = nullptr;
	}
}

void UEquipmentComponent::SetShield(AItemActor* ItemActor)
{
	if (ItemActor != nullptr) {
		ShieldInformation = ItemActor->GetGenericItemInformation().P_ItemInfo;
	}
	else
	{
		ShieldInformation = nullptr;
	}
}

bool UEquipmentComponent::IsEquipped(const FName& ItemCode, const EEquipmentType Type)
{
	switch (Type) {
	case EEquipmentType::WEAPON:
		if (WeaponInformation.IsValid())
		{
			return WeaponInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::ARMOR:
		if (ArmorInformation.IsValid())
		{
			return ArmorInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::GLOVE:
		if (GloveInformation.IsValid())
		{
			return GloveInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::BELT:
		if (BeltInformation.IsValid())
		{
			return BeltInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::HELMET:
		if (HelmetInformation.IsValid())
		{
			return HelmetInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::SHOES:
		if (ShoesInformation.IsValid())
		{
			return ShoesInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::SHOULDER:
		if (ShoulderInformation.IsValid())
		{
			return ShoulderInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;
	case EEquipmentType::SHIELD:
		if (ShieldInformation.IsValid())
		{
			return ShieldInformation.Get()->Item_Code.IsEqual(ItemCode);
		}
		break;

	}

	return false;
}

bool UEquipmentComponent::UnEquip(const FName& ItemCode, const EEquipmentType Type)
{
	APlayerCharacter* Player = GetOwner<APlayerCharacter>();

	switch (Type) {
	case EEquipmentType::WEAPON:
		
			if(WeaponInformation.IsValid())
			{
				if(WeaponInformation.Get()->Item_Code.IsEqual(ItemCode))
				{
					Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)WeaponInformation.Get());
					Player->GetWeapon()->GetEquipmentMeshComponent()->SetStaticMesh(nullptr);
					Player->GetMesh()->SetAnimInstanceClass(DefaultEquipSetting.DefaultAnimBlueprint->GetAnimBlueprintGeneratedClass());
					WeaponInformation = nullptr;

					return true;
				}
			}
		
		break;
	case EEquipmentType::ARMOR:
		if (ArmorInformation.IsValid())
		{
			if (ArmorInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)ArmorInformation.Get());
				Player->GetMesh()->SetSkeletalMesh(DefaultEquipSetting.DefaultArmor);
				ArmorInformation = nullptr;

				return true;
			}
		}
		break;
	case EEquipmentType::GLOVE:
		if (GloveInformation.IsValid())
		{
			if (GloveInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)GloveInformation.Get());
				GloveInformation = nullptr;
				Player->GetGloveMeshComponent()->SetSkeletalMesh(DefaultEquipSetting.DefaultGlove);
				return true;
			}
		}
		break;
	case EEquipmentType::BELT:
		if (BeltInformation.IsValid())
		{
			if (BeltInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)BeltInformation.Get());
				BeltInformation = nullptr;
				Player->GetBeltMeshComponent()->SetSkeletalMesh(nullptr);
				return true;
			}
		}
		break;
	case EEquipmentType::HELMET:
		if (HelmetInformation.IsValid())
		{
			if (HelmetInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)HelmetInformation.Get());
				HelmetInformation = nullptr;
				Player->GetHelmetMeshComponent()->SetSkeletalMesh(nullptr);
				Player->GetHairMeshComponent()->SetSkeletalMesh(DefaultEquipSetting.DefaultHair_Full);
				Player->GetFaceMeshComponent()->SetSkeletalMesh(DefaultEquipSetting.DefaultFace);
				return true;
			}
		}
		break;
	case EEquipmentType::SHOES:
		if (ShoesInformation.IsValid())
		{
			if (ShoesInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)ShoesInformation.Get());
				ShoesInformation = nullptr;
				Player->GetShoesMeshComponent()->SetSkeletalMesh(DefaultEquipSetting.DefaultShoes);
				return true;
			}
		}
		break;
	case EEquipmentType::SHOULDER:
		if (ShoulderInformation.IsValid())
		{
			if (ShoulderInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)ShoulderInformation.Get());
				ShoulderInformation = nullptr;
				Player->GetShoulderMeshComponent()->SetSkeletalMesh(nullptr);
				return true;
			}
		}
		break;
	case EEquipmentType::SHIELD:
		if (ShieldInformation.IsValid())
		{
			if (ShieldInformation.Get()->Item_Code.IsEqual(ItemCode))
			{
				Player->GetStatusComponent()->RemoveStatusValue(*(FEquipment*)ShieldInformation.Get());
				ShieldInformation = nullptr;
				Player->GetShield()->GetEquipmentMeshComponent()->SetStaticMesh(nullptr);
				return true;
			}
		}
		break;
	}

	return false;
}



