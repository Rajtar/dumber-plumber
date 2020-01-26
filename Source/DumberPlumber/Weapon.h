

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamEnum.h"

#include "Weapon.generated.h"

UCLASS()
class DUMBERPLUMBER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	UFUNCTION()
	void SetTeam(ETeamEnum Team);

	UPROPERTY(Replicated, EditAnywhere)
	class UMaterial* RedTeamMaterial;

	UPROPERTY(Replicated, EditAnywhere)
	class UMaterial* BlueTeamMaterial;

	UFUNCTION()
	void WeaponTeamChangedClient();

protected:

	UFUNCTION()
	void SetTeamColor();

	UPROPERTY(ReplicatedUsing = WeaponTeamChangedClient, EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	ETeamEnum Team;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* Mesh;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;

};
