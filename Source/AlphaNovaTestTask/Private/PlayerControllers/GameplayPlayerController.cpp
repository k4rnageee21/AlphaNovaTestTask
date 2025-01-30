#include "PlayerControllers/GameplayPlayerController.h"
#include "GameModes/GameplayGameMode.h"
#include "UI/HUDs/GameplayHUD.h"

void AGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	check(IsValid(World));
	GameplayGM = World->GetAuthGameMode<AGameplayGameMode>();
	GameplayHUD = GetHUD<AGameplayHUD>();
	World->GetTimerManager().SetTimerForNextTick(this, &ThisClass::InitHUD);
}

void AGameplayPlayerController::InitHUD()
{
	if (!IsValid(GameplayGM) || !IsValid(GameplayHUD))
	{
		return;
	}

	GameplayHUD->SetClearerTargetsLeft(GameplayGM->GetClearerTargetsLeft());
	GameplayHUD->SetTargetsDyed(GameplayGM->GetClearTargetsDyed());
	GameplayHUD->SetTargetsAmount(GameplayGM->GetTargetsAmount());
	
	GameplayGM->OnClearerTargetsLeftChanged.AddDynamic(this, &ThisClass::HandleClearerTargetsLeftChanged);
	GameplayGM->OnClearTargetsDyedChanged.AddDynamic(this, &ThisClass::HandleClearTargetsDyedChanged);
}

void AGameplayPlayerController::HandleClearerTargetsLeftChanged(int32 ClearerTargetsLeft)
{
	if (IsValid(GameplayHUD))
	{
		GameplayHUD->SetClearerTargetsLeft(ClearerTargetsLeft);
	}
}

void AGameplayPlayerController::HandleClearTargetsDyedChanged(int32 ClearTargetsDyed)
{
	if (IsValid(GameplayHUD))
	{
		GameplayHUD->SetTargetsDyed(ClearTargetsDyed);
	}
}
