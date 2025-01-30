#pragma once

#include "CoreMinimal.h"
#include "Actors/TargetBase.h"
#include "ClearTarget.generated.h"

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AClearTarget : public ATargetBase
{
	GENERATED_BODY()
	
public:

protected:
	virtual void OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

};
