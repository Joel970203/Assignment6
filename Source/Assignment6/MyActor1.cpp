#include "MyActor1.h"

// Sets default values
AMyActor1::AMyActor1()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Water_Lake.M_Water_Lake"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	// �ʱⰪ ����
	MovementDirection = -1.0f; // �ʱ� ������ �Ʒ���
	MovementSpeed = 200.0f; // �̵� �ӵ� ����
	MaxOffset = -1500.0f; // �ǾƷ�
	MinOffset = -300.0f;  // ����
	CurrentOffset = -300.0f; // �ʱ� �������� -300
	SetActorScale3D(FVector(8.0f, 8.0f, 3.0f));
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� Z ��ǥ�� �������� �̵�
	FVector CurrentLocation = GetActorLocation();
	CurrentOffset = CurrentLocation.Z; // ���� Z ��ǥ�� �������� ���

	// ��ŸŸ�� ��� �̵�
	CurrentOffset += MovementDirection * MovementSpeed * DeltaTime;

	// �̵� ���� ���� �� ���� ��ȯ
	if (CurrentOffset <= MaxOffset) // �ǾƷ��� �����ϸ� �ö󰡱� ����
	{
		CurrentOffset = MaxOffset;
		MovementDirection = 1.0f; // ���� ���� (����)
	}
	else if (CurrentOffset >= MinOffset) // ������ �����ϸ� �������� ����
	{
		CurrentOffset = MinOffset;
		MovementDirection = -1.0f; // ���� ���� (�Ʒ���)
	}

	// ���ο� ��ġ ����
	CurrentLocation.Z = CurrentOffset;
	SetActorLocation(CurrentLocation);
}
