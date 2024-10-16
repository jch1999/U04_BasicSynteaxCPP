#include "CPhysicsCube.h"
#include "BasicSyntaxCPP.h"
#include "Components/StaticMeshComponent.h"

ACPhysicsCube::ACPhysicsCube()
{
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/StaticMeshs/SM_Cube");
	MeshComp->SetStaticMesh(MeshAsset);

	MeshComp->SetRelativeScale3D(FVector(0.5f));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
}

