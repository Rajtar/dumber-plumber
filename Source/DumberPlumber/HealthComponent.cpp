


#include "HealthComponent.h"
#include "DumberPlumberCharacter.h"
#include "Net/UnrealNetwork.h"


UHealthComponent::UHealthComponent()
{
	DefaultHealth = 100.0f;

	SetIsReplicated(true);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
		}
	}

	Health = DefaultHealth;
}

void UHealthComponent::HealthChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("HealthChanged"));
	auto plumber = (ADumberPlumberCharacter*)GetOwner();
	if (plumber)
	{
		UE_LOG(LogTemp, Warning, TEXT("plumber found"));
		plumber->HealthInd();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("plumber not found"));
	}
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}