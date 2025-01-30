#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEndMenuRestartButtonClicked);

class UTargetsWidget;
class UGameEndWidget;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameEndMenuRestartButtonClicked OnGameEndMenuRestartButtonClicked;

	UFUNCTION(BlueprintCallable)
	void SetClearerTargetsLeft(int32 InClearerTargetsLeft);

	UFUNCTION(BlueprintCallable)
	void SetTargetsDyed(int32 InTargetsDyed);

	UFUNCTION(BlueprintCallable)
	void SetTargetsAmount(int32 InTargetsAmount);

	UFUNCTION(BlueprintCallable)
	void AddGameEndWidget();

protected:
	virtual void BeginPlay() override;

	void AddTargetsWidget();

	UFUNCTION()
	void HandleGameEndMenuRestartButtonClicked();

	// Targets Widget Params
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targets Widget")
	TSubclassOf<UTargetsWidget> TargetsWidgetClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	TObjectPtr<UTargetsWidget> TargetsWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsWidgetOrderZ = 0;

	// Game End Widget Params
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game End Widget")
	TSubclassOf<UGameEndWidget> GameEndWidgetClass;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Game End Widget")
	TObjectPtr<UGameEndWidget> GameEndWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game End Widget")
	int32 GameEndWidgetOrderZ = 1;

	// Cached values
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsAmount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Targets Widget")
	int32 TargetsDyed = 0;
};
