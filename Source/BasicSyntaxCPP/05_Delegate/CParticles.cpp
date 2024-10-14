#include "CParticles.h"
#include "BasicSyntaxCPP.h"
#include "Particles/ParticleSystem.h"
#include "Components/TextRenderComponent.h"
#include "CBoxBase_Event.h"

ACParticles::ACParticles()
{
	/*RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;*/
	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");

	/*TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootSceneComp);*/
	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp",RootSceneComp);

	/*ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset1(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/P_AU_Trap_Impact"));
	if (ParticleAsset1.Succeeded())
	{
		Particles[0] = ParticleAsset1.Object;
	}*/
	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/P_AU_Trap_Impact");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "/Game/Explosions/Particles/P_ImpactExplosion4");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "/Game/FXVarietyPack/Particles/P_ky_healAura");

	TextRenderComp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TextRenderComp->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComp->SetTextRenderColor(FColor::Red);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());
}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Event::StaticClass(), Actors);

	if (Actors.Num() < 1)return;

	ACBoxBase_Event* Box = Cast<ACBoxBase_Event>(Actors[0]);
	if (Box == nullptr)return;

	Box->OnBoxEvent.AddUFunction(this, "SpawnEmitter");
}

void ACParticles::SpawnEmitter(int32 InIndex)
{
	ensure(Particles[InIndex]);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
}

