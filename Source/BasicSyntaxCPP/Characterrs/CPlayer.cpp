#include "CPlayer.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, 0, GetControlRotation().Yaw);
	FVector Direction=FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, 0, GetControlRotation().Yaw);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
	// Todo. 나머지 입력 이벤트
}

