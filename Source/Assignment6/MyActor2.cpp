#include "MyActor2.h"
#include "Math/UnrealMathUtility.h" // FMath ���

AMyActor2::AMyActor2()
{
	PrimaryActorTick.bCanEverTick = true;
	DeletionProbability = 0.1f; // �⺻ ���� Ȯ�� 10% ����

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

	RotationSpeed = 90.0f; // �⺻ ȸ�� �ӵ� (�����̳� ���� ����)
	TargetRotationAngle = 360.0f; // ����Ʈ 360�� ȸ��
	CurrentRotationAngle = 0.0f;
	SetActorScale3D(FVector(8.0f, 8.0f, 3.0f));
	// ���� ȸ�� ���� ���� (-1 �Ǵ� 1)
	RotationDirection = FMath::RandBool() ? 1 : -1;
}

void AMyActor2::BeginPlay()
{
	Super::BeginPlay();

	// 5�ʸ��� ���� �˻� 
	GetWorld()->GetTimerManager().SetTimer(DeletionTimerHandle, this, &AMyActor2::AttemptDestroyActor, 5.0f, true);
}

void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentRotationAngle >= TargetRotationAngle)
	{
		CurrentRotationAngle = 0.0f; // ȸ�� �Ϸ� �� �ʱ�ȭ
		RotationDirection = FMath::RandBool() ? 1 : -1; // ���ο� ���� ���� ����
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