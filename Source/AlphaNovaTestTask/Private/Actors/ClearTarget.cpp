#include "Actors/ClearTarget.h"

void AClearTarget::OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDyeable* Dyeable = Cast<IDyeable>(OtherActor);
	if (!Dyeable)
	{
		return;
	}

	// A clear target can only dye another clear target, that's all 
	// (and only if it itself is already dyed and another target isn't already dyed)
	if (bDyed && !Dyeable->IsDyed() && Dyeable->CanBeDyedByTarget())
	{
		Dyeable->Dye(CurrentColor);
	}
}
