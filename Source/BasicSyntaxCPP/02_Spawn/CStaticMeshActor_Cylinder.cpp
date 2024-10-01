#include "CStaticMeshActor_Cylinder.h"

ACStaticMeshActor_Cylinder::ACStaticMeshActor_Cylinder()
{
	// Full Ref Path : "StaticMesh'/Game/StaticMeshs/SM_Cylinder.SM_Cylinder'"
	// Alias Ref Path : "/Game/StaticMeshs/SM_Cylinder"

	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("'/Game/StaticMeshs/SM_Cylinder'"));
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}