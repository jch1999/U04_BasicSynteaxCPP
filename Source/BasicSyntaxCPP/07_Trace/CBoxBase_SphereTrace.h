#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_SphereTrace.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_SphereTrace : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
