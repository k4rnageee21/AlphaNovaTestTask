#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Dyeable.h"
#include "TargetBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTargetBase, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDyedChangedSignature, bool, bDyed);

class UBoxComponent;
class UPhysicsMovementComponent;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API ATargetBase : public AActor, public IDyeable
{
	GENERATED_BODY()
	
public:	
	ATargetBase();

	/* Dyeable Interface Implementation */
	virtual void Dye(const FLinearColor& DyeColor) override;
	virtual bool CanBeDyedByTarget() const override;
	virtual void Clear() override;
	virtual bool IsDyed() const override;

	UPROPERTY(BlueprintAssignable)
	FOnTargetDyedChangedSignature OnTargetDyedChanged;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDyed(bool bInDyed);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	bool bDyed = false;

	// Default color for all the targets (should be equal to the origin color of clear targets)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	FLinearColor BaseTargetColor = FLinearColor::Yellow;

	// Specified color for specific target
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	FLinearColor OriginColor = FLinearColor::Yellow;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	FLinearColor CurrentColor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UPhysicsMovementComponent> PhysicsMovement;
};
