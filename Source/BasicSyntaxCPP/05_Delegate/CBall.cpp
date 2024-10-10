#include "CBall.h"
#include "Components/UStaicMeshComponent.h"

ACBall::ACBall()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		MeshComps[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(SubObjectName));
		MeshComps[i]->SetupAttachment(RootSceneComp);
		MeshComps[i]->SetRelativeLocation(FVector(0, 200 * i, 0));
	}
}

void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
}

