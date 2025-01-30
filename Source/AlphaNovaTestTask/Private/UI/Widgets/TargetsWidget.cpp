#include "UI/Widgets/TargetsWidget.h"
#include "Components/TextBlock.h"
#define LOCTEXT_NAMESPACE "AlphaNovaTestTask"

void UTargetsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetClearerTargetsLeft(0);
	SetTargetsDyed(0, 0);
}

void UTargetsWidget::SetClearerTargetsLeft(int32 ClearerTargetsLeft)
{
	if (IsValid(ClearerTargetsLeftLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("ClearerTargetsLeft", ClearerTargetsLeft);

		FText FormattedText = FText::Format(
			NSLOCTEXT("AlphaNovaTestTask", "ClearerTargetsLeftLabel", "Clearer Targets Left: {ClearerTargetsLeft}"),
			Args
		);

		ClearerTargetsLeftLabel->SetText(FormattedText);
	}
}

void UTargetsWidget::SetTargetsDyed(int32 TargetsDyedAmount, int32 TargetsAmmount)
{
	if (IsValid(TargetsDyedLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("TargetsDyedAmount", TargetsDyedAmount);
		Args.Add("TargetsAmmount", TargetsAmmount);

		FText FormattedText = FText::Format(
			NSLOCTEXT("AlphaNovaTestTask", "TargetsDyedLabel", "Targets Dyed: {TargetsDyedAmount} / {TargetsAmmount}"),
			Args
		);

		TargetsDyedLabel->SetText(FormattedText);
	}
}

#undef LOCTEXT_NAMESPACE
