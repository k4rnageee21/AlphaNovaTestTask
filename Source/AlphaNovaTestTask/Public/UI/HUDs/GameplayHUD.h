#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class UTargetsWidget;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetClearerTargetsLeft(int32 InClearerTargetsLeft);

	UFUNCTION(BlueprintCallable)
	void SetTargetsDyed(int32 InTargetsDyed);

	UFUNCTION(BlueprintCallable)
	void SetTargetsAmount(int32 InTargetsAmount);

protected:
	virtual void BeginPlay() override;

	void AddTargetsWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targets Widget")
	TSubclassOf<UTargetsWidget> TargetsWidgetClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	TObjectPtr<UTargetsWidget> TargetsWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsWidgetOrderZ = 0;

	// Cached values
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsAmount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsDyed = 0;
};
