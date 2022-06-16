// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/02_Component/LockOnComponent.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void ULockOnComponent::OnEndLockOnEvent()
{
	SetComponentTickEnabled(false);
	ClearLockOnActors();
}

// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	OnEndLockOn.AddUniqueDynamic(this, &ULockOnComponent::OnEndLockOnEvent);

	SetComponentTickEnabled(false);

	// ...
	Player = GetOwner<APlayerCharacter>();
	if(Player!=nullptr)
	{
		CameraComponent = Player->GetFollowCamera();
	}
	
}


void ULockOnComponent::CreateCameraTrace()
{
	TArray<FHitResult> Hits;
	FVector EndPoint = (CameraComponent->GetForwardVector() * LockOnDistance) + CameraComponent->GetComponentLocation();


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this,
		CameraComponent->GetComponentLocation(),
		EndPoint,
		Radius,
		ObjectType,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame, Hits, true))
	{

		//걸린 대상들을 저장.
		for (auto i = 0; i < Hits.Num(); i++)
		{
			LockOnableActors_Sort.AddUnique(Hits[i].GetActor());
			LockOnableActors.AddUnique(Hits[i].GetActor());
		}

		//타겟이 비어있는 경우 타겟을 설정해 줍니다.
		if(LockOnTarget == nullptr)
		{
			//걸린 대상들 정렬
			SortLockOnableActors();

			//가장 가까운 대상을 타겟으로 함.
			LockOnTarget = LockOnableActors_Sort[0];
			OnTargetLockOn.Broadcast(LockOnTarget);
			
		}
	}
	else
	{
		//아무것도 걸린 대상이 없으면
		if (LockOnableActors.Num() == 0) {
			//락온해제
			Player->LockOn();
		}
	}
}

void ULockOnComponent::SortLockOnableActors()
{

	if(Player == nullptr)
	{
		return;
	}

	//거리 오름차순 정렬, 람다식
	LockOnableActors_Sort.Sort([this](const AActor& fst, const AActor& sec)
		{
			return Player->GetDistanceTo(&fst) > Player->GetDistanceTo(&sec);
		});

	//일정거리 이상 멀어진 대상을 제거
	for (auto i = 0; i < LockOnableActors_Sort.Num(); i++)
	{
		auto Target = LockOnableActors_Sort[i];
		if (Player->GetDistanceTo(Target) >= 1500.f)
		{
			LockOnableActors_Sort.RemoveAt(i);
			LockOnableActors.Remove(Target);

			if(Target == LockOnTarget)
			{
				if(LockOnableActors.Num() > 0)
				{
					SetNextLockOnTarget();
				}
			}
		}
	}
}

void ULockOnComponent::CameraLookAtTarget()
{
	if(LockOnTarget!=nullptr)
	{
		USpringArmComponent* CameraBoom = Player->GetCameraBoom();

		FVector Start = LockOnTarget->GetActorLocation();
		FVector End = CameraBoom->GetComponentLocation();

		FRotator Rot = (Start - End).Rotation();
		Player->GetController()->SetControlRotation(Rot);

	}
}

void ULockOnComponent::SetNextLockOnTarget()
{
	if(LockOnableActors.Num() > 1)
	{
		AActor* NextTarget = LockOnableActors[0];
		LockOnableActors.RemoveAt(0);
		LockOnableActors.Push(NextTarget);

		if(LockOnTarget == NextTarget)
		{
			SetNextLockOnTarget();
		}else
		{
			LockOnTarget = NextTarget;
			OnTargetLockOn.Broadcast(LockOnTarget);
		}
		
	}
}

void ULockOnComponent::SetPreLockOnTarget()
{
	if (LockOnableActors.Num() > 1)
	{
		AActor* PreTarget = LockOnableActors.Pop();
		LockOnableActors.EmplaceAt(0, PreTarget);

		if (LockOnTarget == PreTarget)
		{
			SetNextLockOnTarget();
		}
		else
		{
			LockOnTarget = PreTarget;
			OnTargetLockOn.Broadcast(LockOnTarget);
		}

	}
}

void ULockOnComponent::ClearLockOnActors()
{
	LockOnableActors.Empty();
	LockOnableActors_Sort.Empty();
	LockOnTarget = nullptr;
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//1.카메라 트레이스로 대상들을 가져옴.
	CreateCameraTrace();
	//2.대상들을 정렬함.
	SortLockOnableActors();
	//3.카메라로 바라봄
	CameraLookAtTarget();
	//4.락온 위젯의 위치를 업데이트 함.
	OnLockOnWigetPosUpdate.Broadcast(LockOnTarget);
}
