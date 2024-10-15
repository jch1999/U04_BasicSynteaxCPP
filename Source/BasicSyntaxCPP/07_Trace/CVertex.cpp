#include "CVertex.h"
#include "BasicSyntaxCPP.h"

ACVertex::ACVertex()
{
	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootSceneComp);

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/StaticMeshs/SM_Sphere");
	MeshComp->SetStaticMesh(MeshAsset);

	UMaterial* MaterialAsset;
	CHelpers::GetAsset(&MaterialAsset, "/Game/StaticMeshs/M_Emissive");
	MeshComp->SetMaterial(0, MaterialAsset);
}

void ACVertex::BeginPlay()
{
	Super::BeginPlay();
	
}

