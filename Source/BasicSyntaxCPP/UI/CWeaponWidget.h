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
};