#include "CBoxBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACBoxBase::ACBoxBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootSceneComp);
	BoxComp->SetRelativeScale3D(FVector(3));
	BoxComp->bHiddenInGame = false;

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootSceneComp);
	TextRenderComp->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TextRenderComp->SetTextRenderColor(FColor::Red);
	//TextRenderComp->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextRenderComp->HorizontalAlignment = EHTA_Center;
	TextRenderComp->Text = FText::FromString(GetName());
}

void ACBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
}

