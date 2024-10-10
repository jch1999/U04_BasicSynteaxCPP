#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Delegate.generated.h"

DECLARE_DELEGATE(FBoxOverlap); // void __FUNCTION__() RetVal�� ��� ��ȯ ����, Param��� �Ű����� ����� ��.
DECLARE_DELEGATE_RetVal_OneParam(FString, FRetValOverlap, FLinearColor); // FString FUNCTION(FLineraColor inParam)

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Delegate : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FBoxOverlap OnBoxBeginOverlap;
	FBoxOverlap OnBoxEndOverlap;

	FRetValOverlap OnRetValOverlap;
};
