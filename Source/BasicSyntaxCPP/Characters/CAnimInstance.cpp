#include "CAnimInstance.h"
#include "weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!TryGetPawnOwner())
	{
		return;
	}

	Speed = TryGetPawnOwner()->GetVelocity().Size2D();

	ICWeaponInterface* Owner = Cast<ICWeaponInterface>(TryGetPawnOwner());
	if (Owner && Owner->GetWeapon())
	{
		bEquipped = Owner->GetWeapon()->IsEquipped();
	}
}