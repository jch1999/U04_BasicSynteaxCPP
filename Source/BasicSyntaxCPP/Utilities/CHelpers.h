#pragma once

#include "CoreMinimal.h"

class CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutAsset,FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		/*check(Asset.Succeeded());
		varifyF(Asset.Succeeded(),"Asset Failed");
		ensureMsgf(Asset.Succeeded());*/
		ensureMsgf(Asset.Succeeded(), TEXT("Asset not found"));

		*OutAsset = Asset.Object;
	}

	template<typename T>
	static void CreateSceneComponent(AActor* InObject, T** OutComp, FName InName, USceneComponent* InParent=nullptr)
	{
		(*OutComp) = InObject->CreateDefaultSubobject<T>(InName);
		if (InParent != nullptr)
		{
			(*OutComp)->SetupAttachment(InParent);
			return;
		}
		//else
		{
			//InObject->RootComponent = (*OutComp);
			InObject->SetRootComponent(*OutComp);
		}
	}
};