#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayPlayerController.generated.h"

class AGameplayHUD;
class AGameplayGameMode;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetUIModeInput();

	UFUNCTION(BlueprintCallable)
	void SetGameplayModeInput();
	
protected:
	virtual void BeginPlay() override;

	void InitPlayerController();
	void InitHUD();

	UFUNCTION()
	void HandleClearerTargetsLeftChanged(int32 ClearerTargetsLeft);

	UFUNCTION()
	void HandleClearTargetsDyedChanged(int32 ClearTargetsDyed);

	UFUNCTION()
	void HandleGameEnd();

	UFUNCTION()
	void HandleGameEndMenuRestartButtonClicked();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameplayHUD> GameplayHUD;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameplayGameMode> GameplayGM;
};
