#include "CMagazine.h"
#include "BasicSyntaxCPP.h"
#include "Components/StaticMeshComponent.h"

ACMagazine::ACMagazine()
{
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/Magazine/SM_AR4_Mag_Empty");
	MeshComp->SetStaticMesh(MeshAsset);
}

void ACMagazine::BeginPlay()
{
	Super::BeginPlay();
	
}

UStaticMeshComponent* ACMagazine::GetMesh()
{
	return MeshComp;
}

