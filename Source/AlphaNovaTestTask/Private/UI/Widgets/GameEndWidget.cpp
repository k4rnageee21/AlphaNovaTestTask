#include "UI/Widgets/GameEndWidget.h"
#include "Components/Button.h"

void UGameEndWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(RestartButton))
	{
		RestartButton->OnClicked.AddDynamic(this, &ThisClass::HandleRestartButtonClicked);
	}
}

void UGameEndWidget::HandleRestartButtonClicked()
{
	OnRestartButtonClicked.Broadcast();
}
