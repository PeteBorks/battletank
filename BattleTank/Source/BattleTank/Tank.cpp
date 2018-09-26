// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}




void ATank::AimAt(FVector OutHitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}


// fire method

	/*	UE_LOG(LogTemp, Warning, TEXT("%s is firing!"), *GetName());

		if (!Barrel) { return; }
		GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
			*/


