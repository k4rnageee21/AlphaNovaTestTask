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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force Params")
	float ForceMagnitude = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force Params")
	float MaxSpeedByForce = 750.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Force Params")
	TObjectPtr<UPrimitiveComponent> OwnerPhysicsRoot;

private:

};
