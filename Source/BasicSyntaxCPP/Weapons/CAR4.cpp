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
	
	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnequipMontage, "/Game/Character/Animations/AR4/Rifle_Ungrab_Montage");

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MontagePlayRate = 1.75f;
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

	OwnerCharacter = Cast<ACharacter>(GetOwner());
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

void ACAR4::EnableAim() { bAiming = true; }

void ACAR4::DisableAim() { bAiming = false; }

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage)return;

	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage,MontagePlayRate);
}

void ACAR4::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACAR4::End_Equip()
{
	bPlayingMontage = false;
}

void ACAR4::Unequip()
{
	if (!bEquipped) return;
	if (bPlayingMontage)return;

	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(UnequipMontage,MontagePlayRate);
}

void ACAR4::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACAR4::End_Unequip()
{
	bPlayingMontage = false;
}
