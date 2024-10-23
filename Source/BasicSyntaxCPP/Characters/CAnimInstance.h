// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BASICSYNTAXCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Pitch;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	bool bEquipped;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	bool bAiming;
};
