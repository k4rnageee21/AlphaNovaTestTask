#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialInstanceDynamicHelper.generated.h"

class UMaterialInstanceDynamic;
class UStaticMeshComponent;

UCLASS()
class ALPHANOVATESTTASK_API UMaterialInstanceDynamicHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Material Instance Dynamic Helper")
	static UMaterialInstanceDynamic* CreateMaterialInstanceOnMesh(UStaticMeshComponent* Mesh);

	UFUNCTION(BlueprintCallable, Category = "Material Instance Dynamic Helper")
	static void SetMaterialInstanceColor(UMaterialInstanceDynamic* Instance, const FLinearColor& Color);
};
