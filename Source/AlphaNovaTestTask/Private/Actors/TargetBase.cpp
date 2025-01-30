#include "Actors/TargetBase.h"
#include "Components/BoxComponent.h"
#include "Components/PhysicsMovementComponent.h"

ATargetBase::ATargetBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	CollisionBox->SetupAttachment(RootComponent);

	PhysicsMovement = CreateDefaultSubobject<UPhysicsMovementComponent>(TEXT("PhysicsMovement"));
	PhysicsMovement->bShouldApplyRandomImpulse = true;
}

void ATargetBase::BeginPlay()
{
	Super::BeginPlay();
	

}
