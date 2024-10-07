#include "CStaticMeshActorBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	RootComponent = MeshComp;

	}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();

	UObject* Asset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/StaticMeshs/MI_StaticMesh"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(Asset);
	if (MaterialAsset)
	{
		DynamicMaterial= UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
		MeshComp->SetMaterial(0, DynamicMaterial);
		
		UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
	}
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACStaticMeshActorBase::ChangeColor()
{
	FLinearColor RandomColor;
	RandomColor.R=UKismetMathLibrary::RandomFloatInRange(0.1f, 1.0f);
	RandomColor.G = UKismetMathLibrary::RandomFloatInRange(0.1f, 1.0f);
	RandomColor.B = UKismetMathLibrary::RandomFloatInRange(0.1f, 1.0f);
	RandomColor.A = 1.0f;
	
	DynamicMaterial->SetVectorParameterValue("BaseColor", RandomColor);

	DynamicMaterial->SetScalarParameterValue("Metalic", RandomColor.R);

	DynamicMaterial->SetScalarParameterValue("Roughness", RandomColor.G);
}

