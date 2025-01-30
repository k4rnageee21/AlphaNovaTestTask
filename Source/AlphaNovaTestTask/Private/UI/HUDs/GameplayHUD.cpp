#include "UI/HUDs/GameplayHUD.h"
#include "GameFramework/PlayerController.h"
#include "UI/Widgets/TargetsWidget.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	AddTargetsWidget();
}

void AGameplayHUD::AddTargetsWidget()
{
	if (!IsValid(TargetsWidgetClass))
	{
		return;
	}

	TargetsWidget = CreateWidget<UTargetsWidget>(GetOwningPlayerController(), TargetsWidgetClass);
	if (IsValid(TargetsWidget))
	{
		TargetsWidget->AddToViewport(TargetsWidgetOrderZ);
	}
}

void AGameplayHUD::SetClearerTargetsLeft(int32 InClearerTargetsLeft)
{
	if (IsValid(TargetsWidget))
	{
		TargetsWidget->SetClearerTargetsLeft(InClearerTargetsLeft);
	}
}

void AGameplayHUD::SetTargetsDyed(int32 InTargetsDyed)
{
	if (IsValid(TargetsWidget))
	{
		TargetsDyed = InTargetsDyed;
		TargetsWidget->SetTargetsDyed(TargetsDyed, TargetsAmount);
	}
}

void AGameplayHUD::SetTargetsAmount(int32 InTargetsAmount)
{
	if (IsValid(TargetsWidget))
	{
		TargetsAmount = InTargetsAmount;
		TargetsWidget->SetTargetsDyed(TargetsDyed, TargetsAmount);
	}
}
