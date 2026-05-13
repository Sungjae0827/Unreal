// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	
	// 1. 소유 폰 가져오기
	auto ownerPawn = TryGetPawnOwner();
	// 2. 플레이어로 캐스팅
	auto player = Cast<ATPSPlayer>(ownerPawn);
	
	if (player)
	{
		// 3. Velocity 획득
		FVector velocity = player->GetVelocity();
		// 4. 전방 벡터 획득
		FVector forwardVector = player->GetActorForwardVector();
		// 5. 내적 계산으로 speed 값 대입
		speed = FVector::DotProduct(forwardVector, velocity);
		// 6. 좌우 속도 할당
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		// 플레이어가 공중에 있는지 확인
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}
