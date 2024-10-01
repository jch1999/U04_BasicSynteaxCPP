#include "CStaticMeshActor_Sphere.h"

ACStaticMeshActor_Sphere::ACStaticMeshActor_Sphere()
{
	// Full Ref Path : "StaticMesh'/Game/StaticMeshs/SM_Cylinder.SM_Cylinder'"
	// Alias Ref Path : "/Game/StaticMeshs/SM_Cylinder"

	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("'/Game/StaticMeshs/SM_Sphere'"));
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}