// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshActor_Cone.h"

ACStaticMeshActor_Cone::ACStaticMeshActor_Cone()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("StaticMesh'/Game/StaticMeshs/SM_Cone.SM_Cone'"));
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}