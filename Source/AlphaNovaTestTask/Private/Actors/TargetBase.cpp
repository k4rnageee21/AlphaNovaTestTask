#include "Actors/TargetBase.h"
#include "Components/BoxComponent.h"
#include "Components/PhysicsMovementComponent.h"
#include "Helpers/MaterialInstanceDynamicHelper.h"

DEFINE_LOG_CATEGORY(LogTargetBase);

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

	MaterialInstanceDynamic = UMaterialInstanceDynamicHelper::CreateMaterialInstanceOnMesh(Mesh);
	if (IsValid(MaterialInstanceDynamic))
	{
		UMaterialInstanceDynamicHelper::SetMaterialInstanceColor(MaterialInstanceDynamic, OriginColor);
	}
	else
	{
		UE_LOG(LogTargetBase, Warning, TEXT("%hs: Can't create material dynamic instance!"), __FUNCTION__);
	}
	CurrentColor = OriginColor;
		
	// We're doing this on overlap collision because a hit event generation during physics simulation isn't the optimal way
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionBoxOverlap);
}

void ATargetBase::OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ATargetBase::SetDyed(bool bInDyed)
{
	bDyed = bInDyed;
	OnTargetDyedChanged.Broadcast(bDyed);
}

void ATargetBase::Dye(const FLinearColor& DyeColor)
{
	if (IsValid(MaterialInstanceDynamic))
	{
		UMaterialInstanceDynamicHelper::SetMaterialInstanceColor(MaterialInstanceDynamic, DyeColor);
	}
	else
	{
		UE_LOG(LogTargetBase, Warning, TEXT("%hs: Invalid material dynamic instance!"), __FUNCTION__);
	}
	CurrentColor = DyeColor;
	UE_LOG(LogTemp, Warning, TEXT("%s : Target has been dyed"), *GetActorLabel());
	SetDyed(true);
}

bool ATargetBase::CanBeDyedByTarget() const
{
	return true;
}

void ATargetBase::Clear()
{
	if (IsValid(MaterialInstanceDynamic))
	{
		UMaterialInstanceDynamicHelper::SetMaterialInstanceColor(MaterialInstanceDynamic, OriginColor);
	}
	else
	{
		UE_LOG(LogTargetBase, Warning, TEXT("%hs: Invalid material dynamic instance!"), __FUNCTION__);
	}
	CurrentColor = OriginColor;
	UE_LOG(LogTemp, Warning, TEXT("%s : Target has been cleared"), *GetActorLabel());
	SetDyed(false);
}

bool ATargetBase::IsDyed() const
{
	return bDyed;
}
