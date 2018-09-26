// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);


public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	// Start moving barrel to crosshair pos
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	int32 ViewportSizeX, ViewportSizeY;
	
	UPROPERTY(EditDefaultsOnly, Category = "CrosshairLocation")
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "CrosshairLocation")
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly, Category = "LineTrace")
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};