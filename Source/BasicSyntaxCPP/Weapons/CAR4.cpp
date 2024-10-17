#include "CAR4.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";
}

//ACAR4* ACAR4::Spawn(ACharacter* InOwner)
//{
//	if (InOwner)
//	{
//		FActorSpawnParameters SpawnParam;
//
//		SpawnParam.Owner = InOwner;
//		return InOwner->GetWorld()->SpawnActor<ACAR4>(WeaponClass, SpawnParam);
//	}
//
//	return nullptr;
//}

void ACAR4::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSocket
		);
	}
}

void ACAR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

