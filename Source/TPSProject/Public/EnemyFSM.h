// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle, Move, Attack, Damage, Die,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EEnemyState mState = EEnemyState::Idle;

	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	//대기 시간
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2;
	//현재 누적 경과 시간
	float currentTime = 0;

	//이동 처리를 우히나 타깃(플레이어) 리퍼런스 변수
	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ATPSPlayer* target;

	UPROPERTY()
	class AEnemy* me; //이 컴포넌트의 부모가 되는 에너미에 대한 리퍼런스 변수

	// 공격 범위
	UPROPERTY(EditAnyWhere, Category=FSM)
	float attackRange = 150.0f;

	// 공격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackDelaytTime = 2.0f;

	// 피격 알림 이벤트 함수
	void OnDamageProcess();

	// 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	int32 hp = 3;
	// 피격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float dieSpeed = 50.0f;
};
