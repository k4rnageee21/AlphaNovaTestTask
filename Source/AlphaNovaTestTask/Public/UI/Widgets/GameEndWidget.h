#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartButtonClicked);

class UButton;

UCLASS(Abstract)
class ALPHANOVATESTTASK_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnRestartButtonClicked OnRestartButtonClicked;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleRestartButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;
};
