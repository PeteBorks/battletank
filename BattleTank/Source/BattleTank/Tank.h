// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintImplementableEvent, Category = "Firing")
	void Fire();

	void AimAt(FVector OutHitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float LaunchSpeed = 10000; // Sensible starting value of 1000m/s


private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local barrel ref for spawning projectile
	UTankBarrel* Barrel = nullptr;
};
