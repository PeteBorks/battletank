// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	ATank * GetControlledTank() const;

	// Start moving barrel to crosshair pos
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	int32 ViewportSizeX, ViewportSizeY;
	
	UPROPERTY(EditAnywhere, Category = CrosshairLocation)
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = CrosshairLocation)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere, Category = LineTrace)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};