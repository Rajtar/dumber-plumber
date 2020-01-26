


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	//Team = ETeamEnum::UNDEFINED;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	MuzzleSocketName = "Muzzle";
	
	SetReplicates(true);
}

void AWeapon::Fire()
{
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (Role < ROLE_Authority)
	{
		ServerFire();
		return;
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

void AWeapon::SetTeam(ETeamEnum Team)
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon  SetTeam  Serwer Previous %s"), /*(this->Team == ETeamEnum::UNDEFINED ? TEXT("UNDEFINED") : */(this->Team == ETeamEnum::RED ? TEXT("RED") : TEXT("BLUE")));
	UE_LOG(LogTemp, Warning, TEXT("AWeapon  SetTeam  Serwer %s"), /*(Team == ETeamEnum::UNDEFINED ? TEXT("UNDEFINED") : */(Team == ETeamEnum::RED ? TEXT("RED") : TEXT("BLUE")));
	this->Team = Team;
	SetTeamColor();
}

void AWeapon::WeaponTeamChangedClient()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon  SetTeam  Client %s"), /*(Team == ETeamEnum::UNDEFINED ? TEXT("UNDEFINED") :*/ (Team == ETeamEnum::RED ? TEXT("RED") : TEXT("BLUE")));
	SetTeamColor();
}

void AWeapon::SetTeamColor()
{
	if (Team == ETeamEnum::RED)
	{
		Mesh->SetMaterial(0, RedTeamMaterial);
	}
	else if (Team == ETeamEnum::BLUE)
	{
		Mesh->SetMaterial(0, BlueTeamMaterial);
	}
}

void AWeapon::ServerFire_Implementation()
{
	Fire();
}

bool AWeapon::ServerFire_Validate()
{
	return true;
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, Team);
	DOREPLIFETIME(AWeapon, RedTeamMaterial);
	DOREPLIFETIME(AWeapon, BlueTeamMaterial);
}