#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsMovementComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsMovementComponent, Log, All);

class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALPHANOVATESTTASK_API UPhysicsMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPhysicsMovementComponent();

	UFUNCTION(BlueprintCallable)
	void MoveByForce(const FVector& MoveVector);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force Params")
	float ForceMagnitude = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force Params")
	float MaxSpeedByForce = 750.f;

	/*
	*	Should be set in the owner's object constructor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse Params")
	bool bShouldApplyRandomImpulse = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse Params")
	float ImpulseApplyingFrequency = 3.f;

protected:
	virtual void BeginPlay() override;

	void InitImpulseMovement();

	UFUNCTION()
	void ApplyRandomImpulse();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UPrimitiveComponent> OwnerPhysicsRoot;

	FTimerHandle ImpulseApplyingTimerHandler;

private:

};
