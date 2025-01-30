#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetsWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API UTargetsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetClearerTargetsLeft(int32 ClearerTargetsLeft);

	UFUNCTION(BlueprintCallable)
	void SetTargetsDyed(int32 TargetsDyedAmount, int32 TargetsAmmount);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ClearerTargetsLeftLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TargetsDyedLabel;
};
