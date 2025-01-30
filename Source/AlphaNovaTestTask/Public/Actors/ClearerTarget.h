#pragma once

#include "CoreMinimal.h"
#include "Actors/TargetBase.h"
#include "ClearerTarget.generated.h"

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AClearerTarget : public ATargetBase
{
	GENERATED_BODY()
	
public:
	AClearerTarget();

	/* Dyeable Interface Implementation */
	virtual void Dye(const FLinearColor& DyeColor) override;
	virtual bool CanBeDyedByTarget() const override;
	virtual void Clear() override;

protected:
	virtual void OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/*
	*	If I understand the condition correctly, after the clearer is dyed for the first time,
	*	it is no longer a clearer, and if cleaned by another cleaner after, it will become
	*	a clean target. So this variable acts as a flag for the correct processing of the clearer logic.
	*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	bool bExpired = false;
};
