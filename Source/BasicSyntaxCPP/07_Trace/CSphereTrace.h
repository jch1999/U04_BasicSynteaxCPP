#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSphereTrace.generated.h"

class UParticleSystemComponent;
class UTextRenderComponent;

UCLASS()
class BASICSYNTAXCPP_API ACSphereTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSphereTrace();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void BeginOverlap(AActor* OverrappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;

private:
	UPROPERTY(EditAnywhere, Category="Physics")
	float Strength;
};
