# 프로젝트 개요

이 프로젝트는 언리얼 엔진에서 **회전용 액터**와 **이동용 액터**를 C++로 구현한 후, 이를 게임 레벨에서 랜덤한 위치에 배치하는 기능을 구현한 것입니다. 게임에서의 **퍼즐 요소**를 자동으로 생성하고, 액터가 일정 시간마다 삭제되거나 이동/회전하는 동작을 실시간으로 확인할 수 있습니다.

## 동영상

[게임 동영상](https://youtu.be/XU7uSd683MY)

## 기능 목록

### 1. 회전용 액터와 이동용 액터가 각기 다른 클래스로 구현되었는가?
- **Yes**

### 2. 각 Actor 클래스가 메쉬를 포함해, 맵에 배치 가능한 형태인가?
- **Yes**

### 3. Blueprint가 아닌 C++ 클래스로서 최소 2개 이상 구현되었는가?
- **Yes**

### 4. Tick 내에서 회전, 이동이 구현되었는가?
- **Yes**

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

### 5. DeltaTime을 곱하여 프레임 독립적인 움직임을 구현했는가?
- **Yes**

### 6. 왕복 이동 로직이 정상적으로 동작하여, 액터가 일정 범위에서 되돌아오는지?
- **Yes**

### 7. UPROPERTY 등을 통해 회전 속도, 이동 속도, 이동 범위 등이 에디터에 노출되어 있는가?
- **Yes**

### 8. 에디터 Details 패널에서 값 수정 시 게임 내 동작이 즉각 반영되는지?
- **Yes**

### 9. 카테고리 설정 (Category="")이 적절히 적용되어 있는가?
- **Yes**

### 10. 스테이지 레벨에 구현한 액터들이 각각 여러 개 배치되었는가?
- **Yes**

### 11. 플레이 모드에서 이동/회전 동작이 의도대로 작동하며, 충돌이나 버그가 없는지?
- **Yes**

### 12. 서로 다른 속도, 각도, 범위를 적용해 테스트해보았는가?
- **Yes**

### 13. Tick 함수가 매 프레임마다 호출된다는 점과, DeltaTime이 프레임 간 경과 시간을 나타낸다는 점을 정확히 인지하고 구현했는가?
- **Yes**

### 14. 시간 보정 로직을 올바르게 적용했는가?
- **Yes**

### 15. Unreal 엔진에서의 리플렉션(UPROPERTY, UFUNCTION 등)을 어떤 목적으로 사용하는지 명확히 이해했는가?
- **Yes**

### 16. 클래스/변수/함수를 에디터나 Blueprint에서 접근 가능하게 만들기 위해 어떤 매크로와 접근 권한이 필요한지 이해하고 있는가?
- **Yes**

## 시간 제한 및 삭제 구현

- **시간 제한 (N초 후 오브젝트 제거, 교체 등)을 구현하고 GetTimerManager().SetTimer(...)를 활용했는가?**
  - **Yes**. 5초마다 10% 확률로 도넛이 삭제되도록 구현.

void AMyActor2::BeginPlay()
{
    Super::BeginPlay();

    // 5초마다 삭제 검사
    GetWorld()->GetTimerManager().SetTimer(DeletionTimerHandle, this, &AMyActor2::AttemptDestroyActor, 5.0f, true);
}

void AMyActor2::AttemptDestroyActor()
{
    if (FMath::FRand() <= DeletionProbability)
    {
        Destroy(); // 10% 확률로 액터를 삭제
    }
}



## 랜덤 스폰

- **랜덤 스폰을 통해 매번 다른 위치/각도로 퍼즐을 생성하는 로직을 구현했는가?**
  - **Yes**. 게임모드 클래스에서 랜덤 스폰을 통해 다양한 위치와 각도로 액터들을 배치했습니다.

```cpp
void AMyGameModeBase::SpawnRandomActors()
{
    const int32 NumActorsToSpawn = 100; // 생성할 액터 수

    for (int32 i = 0; i < NumActorsToSpawn; i++)
    {
        // 랜덤 위치 설정
        FVector RandomLocation(
            FMath::RandRange(0.0f, 8760.0f),
            FMath::RandRange(0.0f, 2920.0f),
            FMath::RandRange(-1800.0f, -300.0f)
        );

        // 랜덤 회전 설정
        FRotator RandomRotation = FRotator(
            0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f
        );

        FActorSpawnParameters SpawnParams;

        // MyActor1 또는 MyActor2를 랜덤하게 생성
        TSubclassOf<AActor> ActorClass = FMath::RandBool() ? AMyActor1::StaticClass() : AMyActor2::StaticClass();

        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, RandomLocation, RandomRotation, SpawnParams);

        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Spawned %s at %s"), *SpawnedActor->GetName(), *RandomLocation.ToString());
        }
    }
}
