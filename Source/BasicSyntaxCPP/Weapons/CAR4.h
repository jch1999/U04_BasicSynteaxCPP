#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;
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
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFiring() { return bAutoFiring; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }
	FORCEINLINE float GetShootRange() { return ShootRange; }

	void ToggleAutoFiring();

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();
	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void OnFire();
	void OffFire();

private:
	// OnFire()안에서만 사용, 타이머에 등록(DynamicDelegate라 UFUNCTION 필요)해 일정시간 마다 발사
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
	float MontagePlayRate;

	UPROPERTY(VisibleDefaultsOnly, Category = "Range")
	float ShootRange;

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
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	float PitchSpeed;
private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
	bool bFiring;
	bool bAutoFiring;

	FTimerHandle AutoFireTimer;

	float CurrentPitch;
};
