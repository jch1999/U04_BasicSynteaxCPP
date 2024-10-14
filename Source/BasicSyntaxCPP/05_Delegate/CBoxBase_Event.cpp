#include "CBoxBase_Event.h"
#include "Kismet/KismetMathLibrary.h"

void ACBoxBase_Event::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Event::BeginOverlap);
}

void ACBoxBase_Event::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OnBoxEvent.Broadcast(UKismetMathLibrary::RandomIntegerInRange(0, 2));
}


// Todo. 위 델리게이트에 바인딩할 함수 만들기