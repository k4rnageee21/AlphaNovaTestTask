#include "Actors/ClearerTarget.h"

AClearerTarget::AClearerTarget()
{
	OriginColor = FLinearColor::Green;
}

void AClearerTarget::Dye(const FLinearColor& DyeColor)
{
	Super::Dye(DyeColor);

	// As soon as it's dyed with the Player Marker, it becomes expired and will act as a clear target
	bExpired = true;
	OriginColor = BaseTargetColor;
	UE_LOG(LogTemp, Warning, TEXT("%s : Clearer target has been dyed and transformed to a clear target"), *GetActorLabel());
}

bool AClearerTarget::CanBeDyedByTarget() const
{
	return bExpired;
}

void AClearerTarget::Clear()
{
	Super::Clear();
	UE_LOG(LogTemp, Warning, TEXT("%s : Clearer target (now it's clear target) has been cleared"), *GetActorLabel());
}

void AClearerTarget::OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDyeable* Dyeable = Cast<IDyeable>(OtherActor);
	if (!Dyeable)
	{
		return;
	}

	if (bExpired)
	{
		// If expired, then act as a clear target
		if (bDyed && !Dyeable->IsDyed() && Dyeable->CanBeDyedByTarget())
		{
			Dyeable->Dye(CurrentColor);
		}
	}
	else
	{
		// If not expired, then act as a clearer target
		// Should clear overlapped target if it's dyed
		if (Dyeable->IsDyed())
		{
			Dyeable->Clear();
		}
	}
}
