#include "CBoxBase_Blueprintable.h"

void ACBoxBase_Blueprintable::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::EndOverlap);
}


void ACBoxBase_Blueprintable::BeginOverlap(AActor* OverrappedActor, AActor* OtherActor)
{
}

void ACBoxBase_Blueprintable::EndOverlap(AActor* OverrappedActor, AActor* OtherActor)
{
}
