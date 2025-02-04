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

	// 초기값 설정
	MovementDirection = -1.0f; // 초기 방향은 아래쪽
	MovementSpeed = 200.0f; // 이동 속도 설정
	MaxOffset = -1500.0f; // 맨아래
	MinOffset = -300.0f;  // 맨위
	CurrentOffset = -300.0f; // 초기 오프셋은 -300
	SetActorScale3D(FVector(8.0f, 8.0f, 3.0f));
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 Z 좌표를 기준으로 이동
	FVector CurrentLocation = GetActorLocation();
	CurrentOffset = CurrentLocation.Z; // 현재 Z 좌표를 기준으로 계산

	// 델타타임 기반 이동
	CurrentOffset += MovementDirection * MovementSpeed * DeltaTime;

	// 이동 범위 제한 및 방향 전환
	if (CurrentOffset <= MaxOffset) // 맨아래에 도달하면 올라가기 시작
	{
		CurrentOffset = MaxOffset;
		MovementDirection = 1.0f; // 방향 반전 (위로)
	}
	else if (CurrentOffset >= MinOffset) // 맨위에 도달하면 내려가기 시작
	{
		CurrentOffset = MinOffset;
		MovementDirection = -1.0f; // 방향 반전 (아래로)
	}

	// 새로운 위치 설정
	CurrentLocation.Z = CurrentOffset;
	SetActorLocation(CurrentLocation);
}
