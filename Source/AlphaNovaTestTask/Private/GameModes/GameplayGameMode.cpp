#include "GameModes/GameplayGameMode.h"
#include "Actors/ClearerTarget.h"
#include "Actors/ClearTarget.h"
#include "Kismet/GameplayStatics.h"

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitGameData();
}

void AGameplayGameMode::InitGameData()
{
	TArray<AActor*> FoundTargets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetBase::StaticClass(), FoundTargets);

	for (AActor* Target : FoundTargets)
	{
		AClearerTarget* ClearerTarget = Cast<AClearerTarget>(Target);
		if (IsValid(ClearerTarget))
		{
			ClearerTarget->OnClearerTargetExpired.AddDynamic(this, &ThisClass::HandleClearerTargetExpired);
			ClearerTargetsLeft++;
		}
		else
		{
			AClearTarget* ClearTarget = Cast<AClearTarget>(Target);
			if (IsValid(ClearTarget))
			{
				ClearTarget->OnTargetDyedChanged.AddDynamic(this, &ThisClass::HandleTargetDyedStatusChanged);
				ClearTargetsAmount++;
			}
		}
	}
}

void AGameplayGameMode::HandleClearerTargetExpired(AClearerTarget* ExpiredClearerTarget)
{
	if (IsValid(ExpiredClearerTarget))
	{
		ExpiredClearerTarget->OnClearerTargetExpired.RemoveDynamic(this, &ThisClass::HandleClearerTargetExpired);
		SetClearerTargetsLeft(ClearerTargetsLeft - 1);
		SetClearTargetsAmount(ClearTargetsAmount + 1);
		SetClearTargetsDyed(ClearTargetsDyed + 1);
		ExpiredClearerTarget->OnTargetDyedChanged.AddDynamic(this, &ThisClass::HandleTargetDyedStatusChanged);
		HandleWinCondition();
	}
}

void AGameplayGameMode::HandleTargetDyedStatusChanged(bool bTargetDyedStatus)
{
	SetClearTargetsDyed(ClearTargetsDyed + (bTargetDyedStatus ? 1 : -1));
	HandleWinCondition();
}

void AGameplayGameMode::SetClearerTargetsLeft(int32 InClearerTargetsLeft)
{
	ClearerTargetsLeft = InClearerTargetsLeft;
	OnClearerTargetsLeftChanged.Broadcast(ClearerTargetsLeft);
}

void AGameplayGameMode::SetClearTargetsAmount(int32 InClearTargetsAmount)
{
	ClearTargetsAmount = InClearTargetsAmount;
	OnClearTargetsAmountChanged.Broadcast(ClearTargetsAmount);
}

void AGameplayGameMode::SetClearTargetsDyed(int32 InClearTargetsDyed)
{
	ClearTargetsDyed = InClearTargetsDyed;
	OnClearTargetsDyedChanged.Broadcast(ClearTargetsDyed);
}

void AGameplayGameMode::HandleWinCondition()
{
	if (IsWinConditionMet())
	{
		HandleGameEnd();
	}
}

bool AGameplayGameMode::IsWinConditionMet()
{
	return ClearerTargetsLeft == 0 && ClearTargetsDyed == ClearTargetsAmount;
}

void AGameplayGameMode::HandleGameEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("You've won!!!"));
}
