#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;
class ICWeaponInterface;
class UStaticMesh;
class ACBullet;
class USoundCue;

UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAR4();

public:
	//static ACAR4* Spawn(ACharacter* InOwner);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsPlayingMontage() { return bPlayingMontage; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE bool IsReloading() { return bReloading; }
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFiring() { return bAutoFiring; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }
	FORCEINLINE float GetShootRange() { return ShootRange; }

	FORCEINLINE FName GetWeaponName() { return WeaponName; }
	FORCEINLINE int32 GetMaxBulletCnt() { return MaxBulletCnt; }
	FORCEINLINE int32 GetCurBulletCnt() { return CurrentBulletCnt; }

	void ToggleAutoFiring();

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();
	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Reload();
	void Begin_Reload();
	void End_Reload();

	void OnFire();
	void OffFire();

private:
	// OnFire()�ȿ����� ���, Ÿ�̸ӿ� ���(DynamicDelegate�� UFUNCTION �ʿ�)�� �����ð� ���� �߻�
	UFUNCTION()
	void Firing_Internal();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* UnequipMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	UAnimMontage* ReloadMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Montage")
	float MontagePlayRate;

	UPROPERTY(VisibleDefaultsOnly, Category = "Range")
	float ShootRange;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
	int32 MaxBulletCnt;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
	int32 CurrentBulletCnt;

	UPROPERTY(VisibleDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Bullet")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UParticleSystem* EjectEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UParticleSystem* ImpactEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	USoundCue* FireSound;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UMaterial* DecalMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category = "Magazine")
	TSubclassOf<ACBullet> MagazineClass;
private:
	ACharacter* OwnerCharacter;

	FName WeaponName;
	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
	bool bFiring;
	bool bReloading;
	bool bAutoFiring;

	FTimerHandle AutoFireTimer;
};
