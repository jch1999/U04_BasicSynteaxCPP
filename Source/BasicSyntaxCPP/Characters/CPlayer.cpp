#include "CPlayer.h"
#include "BasicSyntaxCPP.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "Weapons/CAR4.h"
#include "UI/CAimWidget.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create Camera Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	SpringArmComp->TargetArmLength = 200.0f; // 기본 값은 250 정도?
	SpringArmComp->bUsePawnControlRotation = true; // SpringArm이 있을 때 카메라의 Pitch  회전을 위해 켜두어야 함
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	// Set Skeletal Mesh Asset
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Character/Mesh/SK_Mannequin"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

		ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Game/Player/ABP_CPlayer"));
		if (AnimClass.Succeeded())
		{
			GetMesh()->SetAnimInstanceClass(AnimClass.Class);
		}
	}

	// Backpack
	BackpackComp = CreateDefaultSubobject<UStaticMeshComponent>("BackpackComp");

	ConstructorHelpers::FObjectFinder<UStaticMesh> BackpackMeshAsset(TEXT("/Game/StaticMeshs/Backpack/Backpack"));
	if (BackpackMeshAsset.Succeeded())
	{
		BackpackComp->SetStaticMesh(BackpackMeshAsset.Object);
	}
	BackpackComp->SetupAttachment(GetMesh(), "Backpack");
	
	// Weapon
	CHelpers::GetClass(&WeaponClass, "/Game/AR4/BP_CAR4");

	// Character Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	// Get Aim Widget Class Asset
	CHelpers::GetClass(&AnimWidgetClass, "/Game/UI/WB_Aim");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// Spawn AR4
	
	//ACAR4::Spawn(this);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	AR4=GetWorld()->SpawnActor<ACAR4>(WeaponClass, SpawnParam);

	// Create Aim Widget
	AimWidget = CreateWidget<UCAimWidget>(GetController<APlayerController>(), AnimWidgetClass);
	AimWidget->AddToViewport();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
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

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Rifle", IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayer::OffAim);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction=FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void ACPlayer::OnRifle()
{
	if (AR4->IsEquipped())
	{
		if (AR4->IsAiming())
		{
			OffAim();
		}

		AR4->Unequip();
		return;
	}

	AR4->Equip();
}

void ACPlayer::OnAim()
{
	if (!AR4->IsEquipped())return;
	if (AR4->IsPlayingMontage())return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.0f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	AR4->EnableAim();

	ZoomIn();

	AimWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void ACPlayer::OffAim()
{
	if (!AR4->IsEquipped())return;
	if (AR4->IsPlayingMontage())return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	AR4->DisableAim();

	ZoomOut();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::ResetBodyColor()
{
	SetBodyColor
	(
		FLinearColor(0.45098f, 0.403922f, 0.360784f),
		FLinearColor(0.45098f, 0.403922f, 0.360784f)
	);
}

void ACPlayer::GetAimRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = CameraComp->GetForwardVector();

	FVector MuzzleSocketLocation = AR4->GetMesh()->GetSocketLocation("MuzzleFlash");

	// Get CameraComponent's World Location
	OutAimStart = CameraComp->GetComponentToWorld().GetLocation();
	OutAimEnd = OutAimStart + OutAimDirection * AR4->GetShootRange();
}

