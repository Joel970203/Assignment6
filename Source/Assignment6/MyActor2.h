#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

UCLASS()
class ASSIGNMENT6_API AMyActor2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor2();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	// 회전 속도
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed;

	// 한 번 회전할 각도 
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float TargetRotationAngle;

private:
	float CurrentRotationAngle;
	int32 RotationDirection;
	FTimerHandle DeletionTimerHandle;
	void AttemptDestroyActor();
	// 삭제 확률 
	UPROPERTY(EditAnywhere, Category = "Actor Settings")
	float DeletionProbability;
};
