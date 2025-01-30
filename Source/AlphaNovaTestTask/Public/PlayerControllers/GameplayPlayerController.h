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
	
protected:
	virtual void BeginPlay() override;

	void InitHUD();

	UFUNCTION()
	void HandleClearerTargetsLeftChanged(int32 ClearerTargetsLeft);

	UFUNCTION()
	void HandleClearTargetsDyedChanged(int32 ClearTargetsDyed);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameplayHUD> GameplayHUD;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGameplayGameMode> GameplayGM;
};
