#include "PlayerControllers/GameplayPlayerController.h"
#include "GameModes/GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUDs/GameplayHUD.h"

void AGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerController();
	SetGameplayModeInput();
}

void AGameplayPlayerController::InitPlayerController()
{
	UWorld* World = GetWorld();
	check(IsValid(World));
	GameplayGM = World->GetAuthGameMode<AGameplayGameMode>();
	GameplayHUD = GetHUD<AGameplayHUD>();
	if (IsValid(GameplayGM))
	{
		GameplayGM->OnGameEnd.AddDynamic(this, &ThisClass::HandleGameEnd);
	}
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

void AGameplayPlayerController::SetUIModeInput()
{
	bShowMouseCursor = true;
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
}

void AGameplayPlayerController::SetGameplayModeInput()
{
	bShowMouseCursor = false;
	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
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

void AGameplayPlayerController::HandleGameEnd()
{
	if (IsValid(GameplayHUD))
	{
		GameplayHUD->AddGameEndWidget();
		GameplayHUD->OnGameEndMenuRestartButtonClicked.AddDynamic(this, &ThisClass::HandleGameEndMenuRestartButtonClicked);
	}
	SetUIModeInput();
}

void AGameplayPlayerController::HandleGameEndMenuRestartButtonClicked()
{
	RestartLevel();
}
