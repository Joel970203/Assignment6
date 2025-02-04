#include "MyActor2.h"
#include "Math/UnrealMathUtility.h" // FMath 사용

AMyActor2::AMyActor2()
{
	PrimaryActorTick.bCanEverTick = true;
	DeletionProbability = 0.1f; // 기본 삭제 확률 10% 설정

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Torus.Shape_Torus"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	RotationSpeed = 90.0f; // 기본 회전 속도 (디자이너 조정 가능)
	TargetRotationAngle = 360.0f; // 디폴트 360도 회전
	CurrentRotationAngle = 0.0f;
	SetActorScale3D(FVector(8.0f, 8.0f, 3.0f));
	// 랜덤 회전 방향 설정 (-1 또는 1)
	RotationDirection = FMath::RandBool() ? 1 : -1;
}

void AMyActor2::BeginPlay()
{
	Super::BeginPlay();

	// 5초마다 삭제 검사 
	GetWorld()->GetTimerManager().SetTimer(DeletionTimerHandle, this, &AMyActor2::AttemptDestroyActor, 5.0f, true);
}

void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentRotationAngle >= TargetRotationAngle)
	{
		CurrentRotationAngle = 0.0f; // 회전 완료 후 초기화
		RotationDirection = FMath::RandBool() ? 1 : -1; // 새로운 방향 랜덤 설정
	}

	float RotationDelta = RotationSpeed * DeltaTime * RotationDirection;
	CurrentRotationAngle += FMath::Abs(RotationDelta);

	FRotator NewRotation = StaticMeshComp->GetRelativeRotation();
	NewRotation.Yaw += RotationDelta;

	StaticMeshComp->SetRelativeRotation(NewRotation);
}


void AMyActor2::AttemptDestroyActor()
{
	
	if (FMath::FRand() <= DeletionProbability)
	{
		Destroy(); 
	}

}