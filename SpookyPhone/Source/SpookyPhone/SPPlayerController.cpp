// Fill out your copyright notice in the Description page of Project Settings.

#include "SpookyPhone.h"
#include "SPPlayerController.h"
#include "IHeadMountedDisplay.h"

void ASPPlayerController::UpdateRotation(float DeltaTime)
{
	// Calculate Delta to be applied on ViewRotation
	FRotator DeltaRot(RotationInput);

	FRotator NewControlRotation = GetControlRotation();

	if (PlayerCameraManager)
	{
		PlayerCameraManager->ProcessViewRotation(DeltaTime, NewControlRotation, DeltaRot);
	}

	SetControlRotation(NewControlRotation);

	if (!PlayerCameraManager || !PlayerCameraManager->bFollowHmdOrientation)
	{
		if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHeadTrackingAllowed())
		{
			FQuat HMDOrientation;
			FVector HMDPosition;

			// Disable bUpdateOnRT if using this method.
			GEngine->HMDDevice->GetCurrentOrientationAndPosition(HMDOrientation, HMDPosition);

			// Grab rotaiton of HDM
			FRotator NewViewRotation = HMDOrientation.Rotator();

			// Only keep the yaw component from the controller.
			NewViewRotation.Yaw += NewControlRotation.Yaw;

			// Set our new view rotation
			SetViewRotation(NewViewRotation);
		}
	}

	// Lastly update facing rotation of pawn
	APawn* const P = GetPawnOrSpectator();
	if (P)
	{
		P->FaceRotation(NewControlRotation, DeltaTime);
	}
}

void ASPPlayerController::SetControlRotation(const FRotator& NewRotation)
{
	ControlRotation = NewRotation;

	// Anything that is overriding view rotation will need to 
	// call SetViewRotation() after SetControlRotation().
	SetViewRotation(NewRotation);

	if (RootComponent && RootComponent->bAbsoluteRotation)
	{
		RootComponent->SetWorldRotation(GetControlRotation());
	}
}

// We may need to change this function, such that view rotation is updated
// relative to the facing direction of the pawn (not the camera)
void ASPPlayerController::SetViewRotation(const FRotator& NewRotation)
{
	ViewRotation = NewRotation;
}

// Use this to get our view rotation only
FRotator ASPPlayerController::GetViewRotation() const
{
	return ViewRotation;
}




