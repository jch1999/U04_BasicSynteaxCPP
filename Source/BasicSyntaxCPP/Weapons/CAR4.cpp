#include "CAR4.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "CWeaponInterface.h"
#include "CBullet.h"

static TAutoConsoleVariable<bool> CVarDrawDebugLine(TEXT("IM.DrawDebug"), false, TEXT("Visible AR4 aim line"), ECVF_Cheat);

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);
	
	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnequipMontage, "/Game/Character/Animations/AR4/Rifle_Ungrab_Montage");

	CHelpers::GetClass(&ShakeClass, "/Game/AR4/Shke_Fire");
	CHelpers::GetClass(&BulletClass, "/Game/AR4/BP_CBullet");

	CHelpers::GetAsset(&MuzzleEffect, "/Game/Particles_Rifle/Particles/VFX_Muzzleflash");
	CHelpers::GetAsset(&EjectEffect, "/Game/Particles_Rifle/Particles/VFX_Eject_bullet");
	CHelpers::GetAsset(&ImpactEffect, "/Game/Particles_Rifle/Particles/VFX_Impact_Default");
	CHelpers::GetAsset(&FireSound, "/Game/Sounds/S_RifleShoot_Cue");
	CHelpers::GetAsset(&DecalMaterial, "/Game/Materials/M_Decal");

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MontagePlayRate = 1.75f;
	ShootRange = 10000.0f;
	PitchSpeed = 0.25f;
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

	if (!bAiming) return;

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	// Draw Debug Line
	if (CVarDrawDebugLine.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0U, 3.0f);
	}

	// LineTrace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECC_PhysicsBody,
		QueryParams
	))
	{
		// ?œë??ˆì´???¼ì§?¤ì¸ ê²½ìš°ë§?
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			OwnerInterface->OnTarget();
			return;
		}
	}
	OwnerInterface->OffTarget();
}

void ACAR4::ToggleAutoFiring()
{
	bAutoFiring = !bAutoFiring;
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
	if (bFiring) return;

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

void ACAR4::OnFire()
{
	if (!bEquipped)return;
	if (bPlayingMontage)return;
	
	if (!bAiming) return;
	if (bFiring)return;

	bFiring = true;

	CurrentPitch = 0.0f;

	if (bAutoFiring)
	{
		/*FTimerDelegate Delegate = FTimerDelegate::CreateUFunction(this, &ACAR4::Firing_Internal);
		Delegate.BindUFunction(this, &ACAR4::Firing_Internal);*/

		GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &ACAR4::Firing_Internal, 0.1f, true, 0.f);
		return;
	}
	Firing_Internal();
}

void ACAR4::OffFire()
{
	bFiring = false;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	}
}

void ACAR4::Firing_Internal()
{
	// Get Aim Way

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface)return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	// Camera Shake
	if (!OwnerCharacter) return;
	APlayerController* pc = OwnerCharacter->GetController<APlayerController>();
	if (pc)
	{
		pc->PlayerCameraManager->PlayCameraShake(ShakeClass);
	}

	// Spawn Bullet
	FVector MuzzleLocation = MeshComp->GetSocketLocation("b_gun_muzzleflash");
		
	if (BulletClass)
	{
		GetWorld()->SpawnActor<ACBullet>(BulletClass, MuzzleLocation, Direction.Rotation());
	}

	// PlayEffect
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, "MuzzleFlash");
	}
	if (EjectEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(EjectEffect, MeshComp, "EjectBullet");
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);

	// LineTrace for Visibility
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	// Increase Pitch
	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();
	if (CurrentPitch > -PitchSpeed)
	{
		// OwnerCharacter->GetController()->SetControlRotation
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
		CLog::Print(CurrentPitch, 1);
	}

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel
	(
		Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		QueryParams
	))
	{
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();
		// Spawn Decal
		UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5), Hit.ImpactPoint, ImpactRotation, 6.0f);
		DecalComp->SetFadeScreenSize(0);

		// Play Impact
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ImpactRotation);

		// Add Impulse to PhysicsBody
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (HitComp->IsSimulatingPhysics())
		{
			// Èû = ¹æÇâ(ÇÃ·¹ÀÌ¾î - Ãæµ¹ ¾×ÅÍ) * Å©±â
			Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();
			HitComp->AddImpulseAtLocation(Direction * 3000.0f, OwnerCharacter->GetActorLocation());
		}
	}
}
