#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearerTargetsLeftChangedSignature, int32, ClearerTargetsLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearTargetsDyedChangedSignature, int32, ClearTargetsDyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearTargetsAmountChangedSignature, int32, ClearTargetsAmount);

class AClearerTarget;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnClearerTargetsLeftChangedSignature OnClearerTargetsLeftChanged;

	UPROPERTY(BlueprintAssignable)
	FOnClearTargetsDyedChangedSignature OnClearTargetsDyedChanged;

	UPROPERTY(BlueprintAssignable)
	FOnClearTargetsAmountChangedSignature OnClearTargetsAmountChanged;

protected:
	virtual void BeginPlay() override;

	void InitGameData();

	void HandleWinCondition();
	bool IsWinConditionMet();
	void HandleGameEnd();

	UFUNCTION()
	void HandleClearerTargetExpired(AClearerTarget* ExpiredClearerTarget);

	UFUNCTION()
	void HandleTargetDyedStatusChanged(bool bTargetDyedStatus);

	void SetClearerTargetsLeft(int32 InClearerTargetsLeft);
	void SetClearTargetsAmount(int32 InClearTargetsAmount);
	void SetClearTargetsDyed(int32 InClearTargetsDyed);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 ClearerTargetsLeft = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 ClearTargetsAmount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 ClearTargetsDyed = 0;

};
