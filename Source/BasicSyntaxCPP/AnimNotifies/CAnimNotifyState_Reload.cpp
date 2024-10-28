#include "CAnimNotifyState_Reload.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotifyState_Reload::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Attach To HankSocket
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
		{
			AR4->Begin_Reload();
		}
	}
}

void UCAnimNotifyState_Reload::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// bEquipped=true
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();
		if (AR4)
		{
			AR4->End_Reload();
		}
	}
}
