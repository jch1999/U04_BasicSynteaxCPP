#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;

UCLASS()
class BASICSYNTAXCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UFUNCTION(BlueprintCallable)
	void ResetBodyColor();
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	// Our main view target
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;
};
