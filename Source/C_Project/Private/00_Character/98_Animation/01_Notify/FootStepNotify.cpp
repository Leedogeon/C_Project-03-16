// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Animation/01_Notify/FootStepNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"

void UFootStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		FHitResult Hit;

		FVector StartLocation = MeshComp->GetSocketLocation(SocketName);
		//StartLocation으로 부터 아래로 N만큼의 좌표
		FVector EndLocation = (StartLocation.DownVector * 50.f) + StartLocation;

		FCollisionQueryParams CollisionQueryParams;
		//물체 표면 타입을 읽어옵니다.
		CollisionQueryParams.bReturnPhysicalMaterial = true;
		CollisionQueryParams.AddIgnoredActor(MeshComp->GetOwner());


		if(MeshComp->GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,ECC_Visibility, CollisionQueryParams))
		{

			if (Hit.PhysMaterial != nullptr)
			{
				switch (Hit.PhysMaterial->SurfaceType)
				{
				case EPhysicalSurface::SurfaceType_Default:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), DefaultParticle, Hit.Location);
					break;
					//Ground
				case EPhysicalSurface::SurfaceType1:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), GroundParticle, Hit.Location);
					break;
					//Grass
				case EPhysicalSurface::SurfaceType2:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), GrassParticle, Hit.Location);
					break;
					//Graval
				case EPhysicalSurface::SurfaceType3:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), GravalParticle, Hit.Location);
					break;
					//Snow
				case EPhysicalSurface::SurfaceType4:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), SnowParticle, Hit.Location);
					break;
					//Water
				case EPhysicalSurface::SurfaceType5:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), WaterParticle, Hit.Location);
					break;
					//Wood
				case EPhysicalSurface::SurfaceType6:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), WoodParticle, Hit.Location);
					break;
					//Sand
				case EPhysicalSurface::SurfaceType7:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), SandParticle, Hit.Location);
					break;
					//Ice
				case EPhysicalSurface::SurfaceType8:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), IceParticle, Hit.Location);
					break;
					//Metal
				case EPhysicalSurface::SurfaceType9:
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), MetalParticle, Hit.Location);
					break;
				}

				if (FootStepSound != nullptr) {
					//큐 내부에서 switch 합니다. FootStepCue에셋을 참고하세요.
					UGameplayStatics::SpawnSoundAtLocation(MeshComp->GetWorld(), FootStepSound, Hit.Location)->SetIntParameter("Surface", Hit.PhysMaterial->SurfaceType - 1);
				}
			}
			
		}

		UKismetSystemLibrary::DrawDebugLine(MeshComp, StartLocation, EndLocation, FLinearColor::Blue, 0.3f, 1.f);
	}
}

