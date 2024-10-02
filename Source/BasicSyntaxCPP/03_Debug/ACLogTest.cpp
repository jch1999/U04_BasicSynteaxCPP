// Fill out your copyright notice in the Description page of Project Settings.


#include "ACLogTest.h"
#include "Utilities/CLog.h"

// Sets default values
AACLogTest::AACLogTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AACLogTest::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 10.0f);
	CLog::Print(4, 2, 10.0f, FColor::Red);
	CLog::Print("Test");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

}

// Called every frame
void AACLogTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

