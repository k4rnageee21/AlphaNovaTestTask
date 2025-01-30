#include "Components/PhysicsMovementComponent.h"
#include "Components/PrimitiveComponent.h"

DEFINE_LOG_CATEGORY(LogPhysicsMovementComponent);

UPhysicsMovementComponent::UPhysicsMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UPhysicsMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();
	if (!IsValid(OwnerActor))
	{
		UE_LOG(LogPhysicsMovementComponent, Warning, TEXT("%hs: Invalid owner actor"), __FUNCTION__);
		return;
	}

	OwnerPhysicsRoot = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent());
	if (!IsValid(OwnerPhysicsRoot))
	{
		UE_LOG(LogPhysicsMovementComponent, Warning, TEXT("%hs: Invalid root component! PhysicsMovementComponent works only with UPrimitiveComponent component as a root"), __FUNCTION__);
		return;
	}
}

void UPhysicsMovementComponent::MoveByForce(const FVector& MoveVector)
{
	if (!IsValid(OwnerPhysicsRoot))
	{
		UE_LOG(LogPhysicsMovementComponent, Warning, TEXT("%hs: Invalid root component"), __FUNCTION__);
		return;
	}

	const FVector OwnerVelocity = OwnerPhysicsRoot->GetComponentVelocity();
	const float GroundSpeed = OwnerVelocity.Size2D();
	if (GroundSpeed < MaxSpeedByForce)
	{
		FVector ForceVector = MoveVector * ForceMagnitude;
		OwnerPhysicsRoot->AddForce(ForceVector);
	}
}
