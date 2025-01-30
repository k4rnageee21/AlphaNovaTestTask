#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetBase.generated.h"

class UBoxComponent;
class UPhysicsMovementComponent;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API ATargetBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UPhysicsMovementComponent> PhysicsMovement;
};
