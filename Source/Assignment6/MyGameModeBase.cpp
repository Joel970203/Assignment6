// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyActor1.h"
#include "MyActor2.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnRandomActors();
}

void AMyGameModeBase::SpawnRandomActors()
{
	const int32 NumActorsToSpawn = 30; // ������ ���� ��

	for (int32 i = 0; i < NumActorsToSpawn; i++)
	{
		// ���� ��ġ ����
		FVector RandomLocation(
			FMath::RandRange(3930.0f, 8760.0f),
			FMath::RandRange(-3600.0f, 2920.0f),
			FMath::RandRange(-1800.0f, -300.0f)
		);

		// ���� ȸ�� ����
		FRotator RandomRotation = FRotator(
			0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f
		);

		FActorSpawnParameters SpawnParams;

		// MyActor1 �Ǵ� MyActor2�� �����ϰ� ����
		TSubclassOf<AActor> ActorClass = FMath::RandBool() ? AMyActor1::StaticClass() : AMyActor2::StaticClass();

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, RandomLocation, RandomRotation, SpawnParams);
	}
}
