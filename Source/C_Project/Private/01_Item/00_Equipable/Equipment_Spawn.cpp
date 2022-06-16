// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipable/Equipment_Spawn.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AEquipment_Spawn::AEquipment_Spawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EquipmentMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMeshComponent"));
	EquipmentMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = EquipmentMeshComponent;
}

// Called when the game starts or when spawned
void AEquipment_Spawn::BeginPlay()
{
	Super::BeginPlay();

}

void AEquipment_Spawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

// Called every frame
void AEquipment_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

