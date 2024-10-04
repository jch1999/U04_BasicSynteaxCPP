#include "CDrawDebug.h"
#include "DrawDebugHelpers.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	TargetLocation1 = FVector(0, 0, 0);
	TargetLocation2 = FVector(500, 0, 0);

	TargetLocation3 = FVector(0, 500, 0);
	TargetLocation4 = FVector(500, 500, 0);

	TargetLocation5 = FVector(0, 1000, 0);
	TargetLocation6 = FVector(500, 1000, 0);
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();
	
	FVector WolrdLocation = GetActorLocation() + TargetLocation1;
	Box = FBox(FVector(-50,-100,-50), FVector(50,100,50));
	
	DrawDebugBox(GetWorld(), WolrdLocation + Box.GetCenter(), Box.GetExtent(), FColor::Orange, true);
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WorldLocations[0] = GetActorLocation() + TargetLocation1;
	WorldLocations[1] = GetActorLocation() + TargetLocation2;
	WorldLocations[2] = GetActorLocation() + TargetLocation3;
	WorldLocations[3] = GetActorLocation() + TargetLocation4;
	WorldLocations[4] = GetActorLocation() + TargetLocation5;
	WorldLocations[5] = GetActorLocation() + TargetLocation6;

	DrawDebugSolidBox(GetWorld(), WorldLocations[1] + Box.GetCenter(), Box.GetExtent(), FColor::Purple);
	DrawDebugPoint(GetWorld(), WorldLocations[2], 30.0f, FColor::Red);
	DrawDebugSphere(GetWorld(), WorldLocations[3], 100, 30, FColor::Emerald);
	DrawDebugCircle(GetWorld(), WorldLocations[4], 100, 30, FColor::Cyan);
	//DrawDebugString(GetWorld(), WorldLocations[5],GetName(),nullptr,FColor::Red);

	FVector ArrowStart = WorldLocations[0];
	FVector ArrowEnd = WorldLocations[3];
	DrawDebugDirectionalArrow(GetWorld(), ArrowStart, ArrowEnd, 200.0f, FColor::Black, false, 01, 0U, 10.0f);
}

