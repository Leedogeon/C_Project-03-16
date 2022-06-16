// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/ItemActor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AItemActor::AItemActor()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetVisibility(false);

	SphereComponent->SetCollisionProfileName("ItemPreset");
	SphereComponent->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}


#if WITH_EDITOR
void AItemActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InitItemInformation();
}

#endif

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitItemInformation();
}

void AItemActor::InitItemInformation()
{

	if (Item_Table != nullptr)
	{

		const auto info = GetItemInformation<FItemInformation>();
		if (info != nullptr)
		{
			GenericItemInformation.ItemActorObject = info->ItemActorObject;
			GenericItemInformation.Item_Code = info->Item_Code;
			GenericItemInformation.Item_Description = info->Item_Description;
			GenericItemInformation.Item_Description_Long = info->Item_Description_Long;
			GenericItemInformation.Item_Image = info->Item_Image;
			GenericItemInformation.Item_Name = info->Item_Name;
			GenericItemInformation.Item_Price = info->Item_Price;
			GenericItemInformation.Item_Type = info->Item_Type;

			GenericItemInformation.Item_Count = Item_Count;

			/*
			FPotion* i = new FPotion(*Item_Table->FindRow<FPotion>(Item_Code, ""));
			GenericItemInformation.ptr = MakeShareable(i);

			if(GenericItemInformation.ptr.IsValid())
			{
				FPotion* p = (FPotion*)GenericItemInformation.ptr.Get();
				if(p)
				{
					UE_LOG(LogTemp, Error, TEXT("%f"), p->RecoverHP);
				}
			}
			*/
		}

	}
}


