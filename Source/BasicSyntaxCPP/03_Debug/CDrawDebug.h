#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawDebug.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACDrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDrawDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation1;
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation2;
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation3;
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation4;
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation5;
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocation6;
	
	FBox Box;
	FVector WorldLocations[6];
};
