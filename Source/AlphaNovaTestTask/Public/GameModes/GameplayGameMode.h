#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearerTargetsLeftChangedSignature, int32, ClearerTargetsLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearTargetsDyedChangedSignature, int32, ClearTargetsDyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEndSignature);

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
	FOnGameEndSignature OnGameEnd;

	UFUNCTION(BlueprintPure)
	int32 GetTargetsAmount() const;

	UFUNCTION(BlueprintPure)
	int32 GetClearTargetsDyed() const;

	UFUNCTION(BlueprintPure)
	int32 GetClearerTargetsLeft() const;

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

	/*
	*	Data below could be moved to a separate game state class, but as long
	*	as the game is singleplayer, we're fine
	*/
	void SetClearerTargetsLeft(int32 InClearerTargetsLeft);
	void SetClearTargetsDyed(int32 InClearTargetsDyed);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 ClearerTargetsLeft = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 TargetsAmount = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 ClearTargetsDyed = 0;

	bool bHasGameAlreadyEnded = false;

};
