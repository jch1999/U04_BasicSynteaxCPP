#include "CBall.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/GamePlayStatics.h"
#include "CBoxBase_Multicast.h"
#include "Utilities/CLog.h"

ACBall::ACBall()
{
	Pi = 3.14f;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMeshs/SM_Sphere"));
	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		MeshComps[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(SubObjectName));
		MeshComps[i]->SetupAttachment(RootSceneComp);
		MeshComps[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		
		if (MeshAsset.Succeeded())
		{
			MeshComps[i]->SetStaticMesh(MeshAsset.Object);
		}
	}
}

void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Material Asset
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(
		UMaterialInstanceConstant::StaticClass(),
		nullptr,
		TEXT("/Game/StaticMeshs/MI_StaticMesh"))
	);

	for (int32 i = 0; i < 3; i++)
	{
		// SetWorldLocation of MeshComps
		FTransform TM = MeshComps[i]->GetComponentToWorld(); // Transform의 World상의 값으로 변경해서 반환
		OriginLocations[i] = TM.GetLocation();

		
		// Set Dynamic Material
		if (MaterialAsset)
		{
			DynamicMaterials[i] = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
			MeshComps[i]->SetMaterial(0, DynamicMaterials[i]);
		}
	}

	// Bind Multicast Event
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Multicast::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		ACBoxBase_Multicast* Box = Cast<ACBoxBase_Multicast>(Actors[0]);

		if (Box)
		{
			Box->OnBoxMulticast.AddUObject(this, &ACBall::Drop);

			Box->OnBoxMulticast.AddLambda([&](int32 InIndex, FLinearColor InColor) 
				{
					Pi = 99.0f;
					FString Log = FString::Printf(TEXT("[Pi = %f], RandomIndex is %d"),Pi,InIndex);
					CLog::Log(Log);
				});
		}
	}
}

void ACBall::Drop(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		MeshComps[i]->SetSimulatePhysics(false);
		MeshComps[i]->SetWorldLocation(OriginLocations[i]);

		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FLinearColor(0.25f, 0.25f, 0.25f));
	}

	// 이전에 떨어진 Ball이 다시 선택되면 꺼지고 켜지는 시간이 짧아서 다시 떨어지지 않는다.
	MeshComps[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}

