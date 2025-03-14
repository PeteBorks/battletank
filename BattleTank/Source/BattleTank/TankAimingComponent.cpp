// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel)) { return; }

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams params;
	TArray < AActor * > ActorsToIgnore;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity // Calculate the OutLaunchVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			WorldSpaceAim,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			params,
			ActorsToIgnore,
			false
		);
		if (bHaveAimSolution)
		{
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);

			auto Time = GetWorld()->GetTimeSeconds();
		}
		else
		{
			auto Time = GetWorld()->GetTimeSeconds();
		}

}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{	
	if (!ensure(Barrel || Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01f);
}
