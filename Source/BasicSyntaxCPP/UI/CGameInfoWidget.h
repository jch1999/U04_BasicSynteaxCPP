#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameInfoWidget.generated.h"

class UTextBlock;

UCLASS()
class BASICSYNTAXCPP_API UCGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void EnableAutoFire();

	UFUNCTION(BlueprintNativeEvent)
	void DisableAutoFire();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AutoFireText;
};
