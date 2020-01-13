


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	MuzzleSocketName = "Muzzle";
}

void AWeapon::Fire()
{
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (ProjectileClass)
	{
		FVector MuzzleLocation = Mesh->GetSocketLocation(MuzzleSocketName);
		FRotator MuzzleRotation = Mesh->GetSocketRotation(MuzzleSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		projectile->SetOwner(this);
	}
}
