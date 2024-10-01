#include "CStaticMeshActorBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMeshActorBase::ACStaticMeshActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	RootComponent = MeshComp;

	}

void ACStaticMeshActorBase::BeginPlay()
{
	Super::BeginPlay();

	// Todo. 동적 머티리얼 엣세 얻어오기 -> DynamicMaterial화
	StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr,TEXT("MaterialInstanceConstant'/Game/StaticMeshs/MI_StaticMesh.MI_StaticMesh'"));

	UMaterialInstanceDynamic::Create(, );
}

void ACStaticMeshActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

