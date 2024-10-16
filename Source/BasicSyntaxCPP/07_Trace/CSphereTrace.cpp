#include "CSphereTrace.h"
#include "BasicSyntaxCPP.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Gameframework/Character.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp");
	UParticleSystem* ParticleAsset;
	CHelpers::GetAsset(&ParticleAsset, "/Game/Explosions/Particles/P_ImpactExplosion4");
	ParticleComp->SetTemplate(ParticleAsset);
	ParticleComp->SetAutoActivate(false);

	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp", ParticleComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 20));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->SetTextRenderColor(FColor::Blue);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());

	Strength = 15e+6f; // 15 + 0 6개
}

void ACSphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSphereTrace::BeginOverlap(AActor* OverrappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ACharacter>() == false) return;

	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery4);

	// ECollisionChannel// -> 내 충돌체 타입
	// EObjectTypeQuery// -> 다른 오브젝트의 충돌체 타입
	TArray<AActor*> Ignores;

	TArray<FHitResult> Hits;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		Start,
		End,
		1000,
		ObjectTypes,
		false,
		Ignores,
		EDrawDebugTrace::ForDuration,
		Hits,
		true
	))
	{
		ParticleComp->ResetParticles();
		ParticleComp->SetActive(true);

		for (const FHitResult& Hit : Hits)
		{
			UPrimitiveComponent* HitComp = Hit.GetComponent();
			HitComp->AddRadialImpulse
			(
				GetActorLocation(),
				1000, Strength/HitComp->GetMass(),
				ERadialImpulseFalloff::RIF_Linear
			);
		}
	}
}

