// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/PlayerCharacter.h"

#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/00_Player/02_Component/LockOnComponent.h"
#include "00_Character/00_Player/02_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/00_Player/00_Controller/MainPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetSystemLibrary.h"

APlayerCharacter::APlayerCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 300;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GloveMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GloveMeshComponent"));
	GloveMeshComponent->SetupAttachment(GetMesh());
	GloveMeshComponent->SetMasterPoseComponent(GetMesh());

	BeltMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BeltMeshComponent"));
	BeltMeshComponent->SetupAttachment(GetMesh());
	BeltMeshComponent->SetMasterPoseComponent(GetMesh());

	FaceMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMeshComponent"));
	FaceMeshComponent->SetupAttachment(GetMesh());
	FaceMeshComponent->SetMasterPoseComponent(GetMesh());

	HairMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMeshComponent"));
	HairMeshComponent->SetupAttachment(GetMesh());
	HairMeshComponent->SetMasterPoseComponent(GetMesh());

	HelmetMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMeshComponent"));
	HelmetMeshComponent->SetupAttachment(GetMesh());
	HelmetMeshComponent->SetMasterPoseComponent(GetMesh());

	ShoesMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoesMeshComponent"));
	ShoesMeshComponent->SetupAttachment(GetMesh());
	ShoesMeshComponent->SetMasterPoseComponent(GetMesh());

	ShoulderMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderMeshComponent"));
	ShoulderMeshComponent->SetupAttachment(GetMesh());
	ShoulderMeshComponent->SetMasterPoseComponent(GetMesh());


	WeaponActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponActorComponent"));
	WeaponActorComponent->SetupAttachment(GetMesh(), "hand_rSocket");

	ShieldActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ShieldActorComponent"));
	ShieldActorComponent->SetupAttachment(GetMesh(), "hand_lSocket");

	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));


	SceneCapture2DComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture2DComponent"));
	SceneCapture2DComponent->SetupAttachment(RootComponent);
}


AWeapon_Spawn* APlayerCharacter::GetWeapon()
{
	if(WeaponActorComponent == nullptr)
	{
		return nullptr;
	}

	if (WeaponActorComponent->GetChildActor() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("무기가 비어있어서 비어있는 무기를 생성했습니다."));
		WeaponActorComponent->SetChildActorClass(AWeapon_Spawn::StaticClass());
		WeaponActorComponent->GetChildActor()->SetOwner(this);
		SceneCapture2DComponent->ShowOnlyComponent(Cast<UPrimitiveComponent>(WeaponActorComponent->GetChildActor()->GetRootComponent()));

	}

	return Cast<AWeapon_Spawn>(WeaponActorComponent->GetChildActor());
}

AEquipment_Spawn* APlayerCharacter::GetShield()
{
	if (ShieldActorComponent == nullptr)
	{
		return nullptr;
	}

	if (ShieldActorComponent->GetChildActor() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("쉴드가 비어있어서 비어있는 쉴드를 생성했습니다."));
		ShieldActorComponent->SetChildActorClass(AEquipment_Spawn::StaticClass());
		ShieldActorComponent->GetChildActor()->SetOwner(this);
		SceneCapture2DComponent->ShowOnlyComponent(Cast<UPrimitiveComponent>(ShieldActorComponent->GetChildActor()->GetRootComponent()));

	}

	return Cast<AEquipment_Spawn>(ShieldActorComponent->GetChildActor());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}

}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

}

void APlayerCharacter::TurnAtRate(float Rate)
{	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::LookUpAtRate(float Rate)
{	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::AddControllerYawInput(float Val)
{
	if (!bLockOn) {
		Super::AddControllerYawInput(Val);
	}
	else {
		if (Val > 5.f)
		{
			if(GetWorldTimerManager().TimerExists(NextLockOnTimerHandle) == false)
			{
				GetWorldTimerManager().SetTimer(NextLockOnTimerHandle, LockOnComponent, &ULockOnComponent::SetNextLockOnTarget, 0.2f);
			}
			
		}
		else if (Val < -5.f)
		{
			if (GetWorldTimerManager().TimerExists(PreLockOnTimerHandle) == false)
			{
				GetWorldTimerManager().SetTimer(PreLockOnTimerHandle, LockOnComponent, &ULockOnComponent::SetPreLockOnTarget, 0.2f);
			}

		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::Roll);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);

	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &APlayerCharacter::LockOn);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::PickUp);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);
	PlayerInputComponent->BindAction("Equipment", IE_Pressed, this, &APlayerCharacter::OpenEquipment);

	PlayerInputComponent->BindAction("Quick1", IE_Pressed, this, &APlayerCharacter::PressQuick01);
	PlayerInputComponent->BindAction("Quick2", IE_Pressed, this, &APlayerCharacter::PressQuick02);
	PlayerInputComponent->BindAction("Quick3", IE_Pressed, this, &APlayerCharacter::PressQuick03);
	PlayerInputComponent->BindAction("Quick4", IE_Pressed, this, &APlayerCharacter::PressQuick04);
	PlayerInputComponent->BindAction("Quick5", IE_Pressed, this, &APlayerCharacter::PressQuick05);


	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	

}

void APlayerCharacter::LockOn()
{
	bLockOn = !bLockOn;

	if(bLockOn)
	{
		CameraBoom->CameraRotationLagSpeed = 1.5f;
		CameraBoom->bEnableCameraRotationLag = true;

		LockOnComponent->SetComponentTickEnabled(true);
	}else
	{
		CameraBoom->CameraRotationLagSpeed = 10;
		CameraBoom->bEnableCameraRotationLag = false;

		LockOnComponent->OnEndLockOn.Broadcast();
	}

}



void APlayerCharacter::StopRun()
{
	SetActionState(EActionState::NORMAL);
}

void APlayerCharacter::Roll()
{
	if(GetCharacterMovement()->IsFalling())
	{
		return;
	}

	SetActionState(EActionState::ROLL);
	/*
	if (ActionState != EActionState::ROLL && StatusComponent->CheckSP(30.f)) {
		StatusComponent->AddSP(-30.f);
		SetActionState(EActionState::ROLL);
	}
	*/
}

void APlayerCharacter::Attack()
{
	bPressAttack = true;

	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	SetActionState(EActionState::ATTACK);
	/*
	if (ActionState != EActionState::ATTACK && StatusComponent->CheckSP(25.f)) {
		StatusComponent->AddSP(-25.f);
		SetActionState(EActionState::ATTACK);
	}
	*/
}

void APlayerCharacter::StopAttack()
{
	bPressAttack = false;
}

void APlayerCharacter::PickUp()
{
	TArray<AActor*> OverlappedActors;
	GetCapsuleComponent()->GetOverlappingActors(OverlappedActors, AItemActor::StaticClass());

	if(OverlappedActors.Num() > 0)
	{
		UGameplayStatics::SpawnSound2D(this, PickUpItemSound);
		InventoryComponent->AddItem(OverlappedActors[0]);
	}
}

void APlayerCharacter::OpenInventory()
{
	GetController<AMainPlayerController>()->OnOpenInventory.Broadcast();
}

void APlayerCharacter::OpenEquipment()
{
	GetController<AMainPlayerController>()->OnOpenEquipment.Broadcast();
}

void APlayerCharacter::Run()
{
	SetActionState(EActionState::RUN);
}

void APlayerCharacter::SetActionState(EActionState newState)
{


	switch (newState) {
	case EActionState::NORMAL:
		GetCharacterMovement()->MaxWalkSpeed = 300;
		break;
	case EActionState::RUN:
		GetCharacterMovement()->MaxWalkSpeed *= 1.3f;
		break;
	case EActionState::ROLL:
		GetWeapon()->Roll();
		break;
	case EActionState::ATTACK:
		GetWeapon()->Attack();
		break;
	case EActionState::JUMP:

		break;
	}

	ActionState = newState;
}

void APlayerCharacter::Jump()
{
	if (ActionState == EActionState::NORMAL || ActionState == EActionState::RUN)
	{
		Super::Jump();
	}
}

void APlayerCharacter::LookAtLockOnTarget()
{
	if (bLockOn)
	{
		auto Target = LockOnComponent->GetLockOnTarget();
		if (Target != nullptr)
		{
			FRotator Rot = (Target->GetActorLocation() - GetActorLocation()).Rotation();
			Rot.Pitch = GetActorRotation().Pitch;
			Rot.Roll = GetActorRotation().Roll;
			SetActorRotation(Rot);
		}
	}
}

void APlayerCharacter::PressQuick01()
{
	InventoryComponent->UseQuickItem(0);
}

void APlayerCharacter::PressQuick02()
{
	InventoryComponent->UseQuickItem(1);
}

void APlayerCharacter::PressQuick03()
{
	InventoryComponent->UseQuickItem(2);
}

void APlayerCharacter::PressQuick04()
{
	InventoryComponent->UseQuickItem(3);
}

void APlayerCharacter::PressQuick05()
{
	InventoryComponent->UseQuickItem(4);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto weapon = GetWeapon();
	if(weapon!=nullptr)
	{
		weapon->SetOwner(this);
	}

	OnActorBeginOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnBeginOverlapEvent);
	OnActorEndOverlap.AddUniqueDynamic(this, &APlayerCharacter::OnEndOverlapEvent);

	SceneCapture2DComponent->ShowOnlyComponent(GetMesh());
	for (auto i = 0; i < GetMesh()->GetNumChildrenComponents(); i++) {

		SceneCapture2DComponent->ShowOnlyComponent(Cast<UPrimitiveComponent>(GetMesh()->GetChildComponent(i)));
	}
}

void APlayerCharacter::OnBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{

	if(OtherActor != nullptr && OtherActor->IsA<AItemActor>())
	{
		AItemActor* Item = Cast<AItemActor>(OtherActor);
		Item->GetWidgetComponent()->SetVisibility(true);
	}
}

void APlayerCharacter::OnEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && OtherActor->IsA<AItemActor>())
	{
		AItemActor* Item = Cast<AItemActor>(OtherActor);
		Item->GetWidgetComponent()->SetVisibility(false);
	}
}

