#include "Helpers/MaterialInstanceDynamicHelper.h"
#include "Components/StaticMeshComponent.h"

const FName MaterialInstanceColorParameterName = FName(TEXT("Color"));

UMaterialInstanceDynamic* UMaterialInstanceDynamicHelper::CreateMaterialInstanceOnMesh(UStaticMeshComponent* Mesh)
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;
	if (IsValid(Mesh))
	{
		UMaterialInterface* Material = Mesh->GetMaterial(0);
		if (IsValid(Material))
		{
			MaterialInstanceDynamic = Mesh->CreateDynamicMaterialInstance(0, Material);
		}
	}
	return MaterialInstanceDynamic;
}

void UMaterialInstanceDynamicHelper::SetMaterialInstanceColor(UMaterialInstanceDynamic* Instance, const FLinearColor& Color)
{
	if (IsValid(Instance))
	{
		Instance->SetVectorParameterValue(MaterialInstanceColorParameterName, Color);
	}
}
