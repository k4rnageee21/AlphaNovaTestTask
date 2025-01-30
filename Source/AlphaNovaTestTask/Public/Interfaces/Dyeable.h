#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Dyeable.generated.h"

UINTERFACE(MinimalAPI)
class UDyeable : public UInterface
{
	GENERATED_BODY()
};

class ALPHANOVATESTTASK_API IDyeable
{
	GENERATED_BODY()

public:
	virtual void Dye(const FLinearColor& DyeColor) = 0;
	virtual bool CanBeDyedByTarget() const = 0;
	virtual void Clear() = 0;
	virtual bool IsDyed() const = 0;
};
