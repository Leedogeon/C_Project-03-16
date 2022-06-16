// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowActor.generated.h"

UCLASS()
class C_PROJECT_API AArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrowActor();

protected:

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* ArrowMesh;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ArrowMovement;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
