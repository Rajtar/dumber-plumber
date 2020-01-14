// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameFramework/PawnMovementComponent.h"
#include "DumberPlumberCharacter.h"
#include "DumberPlumberProjectile.h"
#include "DumberPlumberPipeActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ADumberPlumberCharacter

ADumberPlumberCharacter::ADumberPlumberCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	Died = false;
	WeaponAttachSocketName = "GripPoint";

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(false);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ADumberPlumberCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);

	if (Role == ROLE_Authority)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Weapon = GetWorld()->SpawnActor<AWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (Weapon)
		{
			Weapon->SetOwner(this);
			Weapon->AttachToComponent(GetMesh1P(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponAttachSocketName);
		}
	}

	HealthComponent->OnHealthChanged.AddDynamic(this, &ADumberPlumberCharacter::OnHealthChanged);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADumberPlumberCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADumberPlumberCharacter::OnFire);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &ADumberPlumberCharacter::UseFocusedInteractable);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADumberPlumberCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADumberPlumberCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADumberPlumberCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADumberPlumberCharacter::LookUpAtRate);
}

void ADumberPlumberCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!IsLocallyControlled())
	{
		FRotator NewRot = FirstPersonCameraComponent->RelativeRotation;
		NewRot.Pitch = RemoteViewPitch * 360.0f / 255.0f;

		FirstPersonCameraComponent->SetRelativeRotation(NewRot);
	}
	UpdateFocusedInteractable();
}

void ADumberPlumberCharacter::OnFire()
{
	if (Weapon == nullptr)
	{
		return;
	}
	Weapon->Fire();
	//OnServerFire();
	//
	//// try and play the sound if specified

		// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}
void ADumberPlumberCharacter::OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHealthChanged: %s"), *FString::SanitizeFloat(Health));
	if (Health <= 0 && !Died)
	{
		Died = true;

		//GetCharacterMovement()->StopActiveMovement();
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();
		//SetLifeSpan(10.0f);
	}
}
//
//void ADumberPlumberCharacter::OnServerFire_Implementation()
//{
//	//// try and fire a projectile
//	//if (ProjectileClass != NULL)
//	//{
//	//	UWorld* const World = GetWorld();
//	//	if (World != NULL)
//	//	{
//	//		const FRotator SpawnRotation = GetControlRotation();
//	//		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
//	//		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
//
//	//		//Set Spawn Collision Handling Override
//	//		FActorSpawnParameters ActorSpawnParams;
//	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//	//		// spawn the projectile at the muzzle
//	//		World->SpawnActor<ADumberPlumberProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//
//	//	}
//	//}
//}
//
//bool ADumberPlumberCharacter::OnServerFire_Validate()
//{
//	return true;
//}


void ADumberPlumberCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADumberPlumberCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADumberPlumberCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADumberPlumberCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADumberPlumberCharacter::UpdateFocusedInteractable()
{
	if (Controller && Controller->IsLocalPlayerController())
	{
		FVector CameraPosition;
		FRotator CameraRotation;
		Controller->GetPlayerViewPoint(CameraPosition, CameraRotation);
		
		const FVector StartTrace = CameraPosition;
		const FVector Direction = CameraRotation.Vector();
		const FVector EndTrace = StartTrace + Direction * MaxInteractionDistance;
		FHitResult HitResult;
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility))
		{
			IInteractable* Interactable = Cast<IInteractable>(HitResult.GetActor());
			if (Interactable)
			{
				FocusedInteractable = Interactable;
				FocusedInteractable->MarkAsFocused();
				return;
			}
		}
		if (FocusedInteractable)
		{
			FocusedInteractable->UnmarkAsFocused();
		}
		FocusedInteractable = nullptr;
	}
}

void ADumberPlumberCharacter::UseFocusedInteractable()
{
	if (GrabbedPipe)
	{
		GrabbedPipe->DropPipe();
		GrabbedPipe = nullptr;
		return;
	}
	if (FocusedInteractable)
	{
		FocusedInteractable->Interact(this);
	}
}

void ADumberPlumberCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADumberPlumberCharacter, Weapon);
}