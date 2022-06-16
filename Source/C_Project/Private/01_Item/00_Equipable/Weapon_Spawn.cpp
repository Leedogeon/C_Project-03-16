// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipable/Weapon_Spawn.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Components/SceneCaptureComponent2D.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWeapon_Spawn::AWeapon_Spawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EquipmentMeshComponent->SetCollisionProfileName("WeaponPreset");
	SetActorEnableCollision(false);

	TrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailComponent"));
	TrailComponent->SetupAttachment(RootComponent);


}

void AWeapon_Spawn::AddUniqueHitActor(AActor* HitActor)
{
	HitActors.AddUnique(HitActor);
}

bool AWeapon_Spawn::IsAlreadyHitActor(AActor* HitActor)
{
	return HitActors.Contains(HitActor);
}

void AWeapon_Spawn::ClearHitActors()
{
	HitActors.Empty();
}

// Called when the game starts or when spawned
void AWeapon_Spawn::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon_Spawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddUniqueDynamic(this, &AWeapon_Spawn::OnActorBeginOverlapEvent);

	if (GetOwner() != nullptr)
	{
		GetOwner<APlayerCharacter>()->GetSceneCapture2DComponent()->
			ShowOnlyComponent(EquipmentMeshComponent);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null"));
	}
	
}

void AWeapon_Spawn::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr)
	{
		FHitResult Hit;
		if(UKismetSystemLibrary::LineTraceSingle(this,
			GetActorLocation(),
			OtherActor->GetActorLocation(),
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForOneFrame,
			Hit,
			true))
		{
			//UGameplayStatics::SpawnEmitterAtLocation(this,HitParticle,Hit.ImpactPoint);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitParticle, Hit.ImpactPoint);

			FPointDamageEvent PointDamageEvent;
			PointDamageEvent.HitInfo = Hit;

			OtherActor->TakeDamage(10.f, 
				PointDamageEvent, 
				GetOwner<ABaseCharacter>()->GetController(), 
				this);
		}



	}
}

// Called every frame
void AWeapon_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Spawn::Attack()
{
	auto Player = GetOwner<APlayerCharacter>();
	if (Player != nullptr)
	{
		const TSharedPtr<FItemInformation>& Info = Player->GetEquipmentComponent()->GetWeapon();
		if (Info.IsValid()) {
			FWeapon* WeaponInfo = (FWeapon*)(Info.Get());
			auto StatComp = Player->GetStatusComponent();
			if ((Player->GetActionState() == EActionState::NORMAL || Player->GetActionState()==EActionState::RUN) && StatComp->CheckSP(WeaponInfo->AttackSP)) {

				Player->LookAtLockOnTarget();
				StatComp->AddSP((-1) * WeaponInfo->AttackSP);
				Player->GetMesh()->GetAnimInstance()->Montage_Play(WeaponInfo->AttackMontage, StatComp->GetStatusValue().ActionSpeed);
			}
		}
	}
}

void AWeapon_Spawn::Roll()
{

	auto Player = GetOwner<APlayerCharacter>();
	if (Player != nullptr)
	{
		const TSharedPtr<FItemInformation>& Info = Player->GetEquipmentComponent()->GetWeapon();
		if (Info.IsValid())
		{
			auto StatComp = Player->GetStatusComponent();
			const auto WeaponInfo = (FWeapon*)Info.Get();
			if (Player->GetActionState() != EActionState::ROLL && StatComp->CheckSP(WeaponInfo->RollSP)) {
				const auto& Status = StatComp->GetStatusValue();
				StatComp->AddSP(WeaponInfo->RollSP * (-1));
				
				float Time = Player->GetMesh()->GetAnimInstance()->Montage_Play(WeaponInfo->RollMontage, Status.ActionSpeed,EMontagePlayReturnType::Duration);
				FTimerHandle rollTimerHandle;
				FTimerDelegate rollTimerDel = FTimerDelegate::CreateUObject(Player, &APlayerCharacter::SetActionState, EActionState::NORMAL);

				GetWorldTimerManager().SetTimer(rollTimerHandle, rollTimerDel, Time, false);
			}
		}

	}
}

