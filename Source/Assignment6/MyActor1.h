#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor1.generated.h"

UCLASS()
class ASSIGNMENT6_API AMyActor1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor1();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 이동 방향 (아래로 또는 위로)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MovementDirection;

	// 현재 Z 좌표 기준 오프셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Settings")
	float CurrentOffset;

	// 맨위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxOffset;

	// 맨아래
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MinOffset;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MovementSpeed;

	// 필요한 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
};
