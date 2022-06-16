// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/00_Equipable/Equipment_Spawn.h"
#include "Weapon_Spawn.generated.h"

/*
 *	플레이어나 NPC, 몬스터가 장착하는 액터입니다.
 *	플레이어의 경우 WeaponActorComponent내부 ChildActor로 이 클래스가 할당됩니다.
 */
UCLASS()
class C_PROJECT_API AWeapon_Spawn : public AEquipment_Spawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Spawn();

protected:

	UPROPERTY()
		TArray<AActor*> HitActors;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* TrailComponent;
public:
	class UParticleSystemComponent* GetTrailComponent() { return TrailComponent; }

	//히트된 대상을 저장
	void AddUniqueHitActor(AActor* HitActor);
	//이미 히트한 대상인지 확인. 맞으면 참
	bool IsAlreadyHitActor(AActor* HitActor);
	//히트 액터 배열을 비움.
	void ClearHitActors();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override; 
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//이제 사용되지 않습니다. 파티클 정보는 장비컴포넌트 내부 무기정보에서 찾을 수 있습니다.
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* HitParticle;

	//플레이어가 공격키를 누르면 호출됩니다.
	void Attack();
	//플레이어가 구르기 키를 누르면 호출됩니다.
	void Roll();
};
