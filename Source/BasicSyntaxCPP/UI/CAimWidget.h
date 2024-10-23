#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAimWidget.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCAimWidget : public UUserWidget
{
	GENERATED_BODY()
	
		// Design -> 
		// Graph -> Code
public:
	// Dot Image to red color

	UFUNCTION(BlueprintImplementableEvent)
	void OnTarget();

	// Dot Image to white color

	UFUNCTION(BlueprintImplementableEvent)
	void OffTarget();
};
