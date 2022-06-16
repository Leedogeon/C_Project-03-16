// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Consume/00_Potion/SPPotionActor.h"

void ASPPotionActor::InitItemInformation()
{
	Super::InitItemInformation();

	if (GenericItemInformation.P_ItemInfo.IsValid()) {

		FPotion* Potion = (FPotion*)GenericItemInformation.P_ItemInfo.Get();

		TArray< FStringFormatArg > args;
		args.Emplace(FStringFormatArg(FString::FormatAsNumber(Potion->RecoverSP)));

		GenericItemInformation.Item_Description = FString::Format(*GenericItemInformation.Item_Description, args);

	}
}
