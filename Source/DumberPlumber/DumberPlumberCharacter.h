// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeamEnum.h"


#include "DumberPlumberCharacter.generated.h"

class ADumberPlumberPipeActor;
class IInteractable;
class UInputComponent;
enum class ETeamEnum : uint8;

UCLASS(config=Game)
class ADumberPlumberCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ADumberPlumberCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBuildComponent* BuildComponent;

	UPROPERTY(Replicated)
	class AWeapon* Weapon;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxInteractionDistance;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Gameplay)
	ADumberPlumberPipeActor* GrabbedPipe;

	UPROPERTY(Replicated)
	ADumberPlumberPipeActor* FocusedInteractable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponAttachSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> StarterWeaponClass;

	void Tick(float DeltaSeconds) override;
	
protected:
	
	///** Fires a projectile. */
	void OnFire();

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComp, float Health, float HealthDelta,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//UFUNCTION(Server, Reliable, WithValidation)
	//void OnServerFire();
  
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void UpdateFocusedInteractable();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUpdateFocusedInteractable();

	void LightUpTheObject();

	void UseFocusedInteractable();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUseFocusedInteractable();

	UPROPERTY(Replicated, BlueprintReadOnly, Category="Player")
	bool Died;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION()
	void DetermineTeam();

	UFUNCTION()
	void SetTeamColor();

	UPROPERTY(ReplicatedUsing = PlayerTeamChangedClient)
	ETeamEnum Team;

	IInteractable* highlightRef;

public:
	UFUNCTION(BlueprintImplementableEvent, Category="Health")
	void HealthInd();

	UFUNCTION()
	void PlayerTeamChangedClient();

	UPROPERTY(Replicated, EditAnywhere)
	class UMaterial* RedTeamMaterial;

	UPROPERTY(Replicated, EditAnywhere)
	class UMaterial* BlueTeamMaterial;

	UFUNCTION()
	ETeamEnum GetTeam();

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

