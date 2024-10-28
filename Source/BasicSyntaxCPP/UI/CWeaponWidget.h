#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWeaponWidget.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeParam(FName Name, int32 NowBulletCnt, int32 MaxBulletCnt);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponName(FName Name);


	UFUNCTION(BlueprintImplementableEvent)
	void SetCurBulletCnt(int32 NowBulletCnt);

	UFUNCTION(BlueprintImplementableEvent)
	void SetMaxBulletCnt(int32 MaxBulletCnt);
};
