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

	// �̵� ���� (�Ʒ��� �Ǵ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MovementDirection;

	// ���� Z ��ǥ ���� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Settings")
	float CurrentOffset;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxOffset;

	// �ǾƷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MinOffset;

	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MovementSpeed;

	// �ʿ��� ������Ʈ ����
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
};
