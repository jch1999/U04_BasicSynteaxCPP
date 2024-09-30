// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshActor_Cube.h"

ACStaticMeshActor_Cube::ACStaticMeshActor_Cube()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("StaticMesh'/Game/StaticMeshs/SM_Cube.SM_Cube'"));
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}