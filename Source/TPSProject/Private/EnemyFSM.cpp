// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyFSM.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// 월드에서 플레이어 리퍼런스 획득
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
	target = Cast<ATPSPlayer>(actor); // 가져온 Actor 타입 인스턴스를 실제 플레이어 타입으로 캐스팅
	me = Cast<AEnemy>(GetOwner());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, logMsg);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}
void UEnemyFSM::IdleState()
{
	//시간 누적시키고
	currentTime += GetWorld()->DeltaTimeSeconds;
	//지정 시간만큼 지나면 Move로
	if (currentTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		currentTime = 0;
	}
}
void UEnemyFSM::MoveState()
{
	// 1. 타깃 목적지
	FVector destination = target->GetActorLocation();
	// 2. 방향 벡터
	FVector dir = destination - me->GetActorLocation();
	// 3. 이동
	me->AddMovementInput(dir.GetSafeNormal());

	// 타깃과의 거리가 지정 미만이 되면 곡격 상태로 전환
	if (dir.Size() < attackRange)
	{
		mState = EEnemyState::Attack;
	}
}
void UEnemyFSM::AttackState()
{
	// 시간 누적을 통해 공격 상태로 전환
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelaytTime)
	{
		// 공격 처리
		currentTime = 0;
	}

	// 플레이어와의 거리를 확인하여 다시 이동으로 전환
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
	}
}
void UEnemyFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0;
	}
}
void UEnemyFSM::DieState()
{
	// 등속도로 아래를 향해 내려간다
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		me->Destroy();
	}
}
void UEnemyFSM::OnDamageProcess()
{
	//me->Destroy();
	hp -= 1;
	if (hp > 0)
	{
		mState = EEnemyState::Damage;
	}
	else
	{
		mState = EEnemyState::Die;
		// 캡슐 컴포넌트 비활성화
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

