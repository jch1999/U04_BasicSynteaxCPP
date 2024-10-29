#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMagazine();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

public:	
	UStaticMeshComponent* GetMesh();
};
