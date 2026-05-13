// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camara)
	class UCameraComponent* tpsCamComp;
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputMappingContext* imc_TPS;
	UPROPERTY(EditDefaultsOnly, category="Input")
	class UInputAction* ia_LookUp;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;

	//좌우 입력 처리
	void Turn(const struct FInputActionValue& inputValue);
	//상하 회전 입력 처리
	void LookUp(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;
	//이동속도
	UPROPERTY(EditAnywhere, category = PalyerSetting)
	float walkSpeed = 200;
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;
	//이동방향
	FVector direction;

	void Move(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Jump;
	void InputJump(const struct FInputActionValue& inputValue);

	void PlayerMove();

	UPROPERTY(VisibleAnywhere, Category=GunMesh)
	class USkeletalMeshComponent* gunMeshcomp;

	//총알
	UPROPERTY(EditDefaultsOnly, Category=BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Fire;

	void InputFire(const struct FInputActionValue& inputValue);

	//스나이퍼건 스태틱메시 추가
	UPROPERTY(VisibleAnywhere, Category=GunMesh)
	class UStaticMeshComponent* sniperGunComp;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* ia_GrenadeGun;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* ia_SniperGun;
	//유탄총 사용 여부
	bool bUsingGrenadeGun = true;
	//유탄총으로 변경
	void ChangeToGrenadeGun(const struct FInputActionValue& inputValue);
	//스나이퍼건으로 변경
	void ChangeToSniperGun(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Sniper;
	
	void SniperAim(const struct FInputActionValue& inputValue);
	bool bSniperAim = false;	//스나이퍼 모드 여부

	//에디터에서 세팅하기 위한 코드
	UPROPERTY(EditDefaultsOnly, Category=SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;
	//스나이퍼 UI 위젯 인스턴스
	UPROPERTY()
	class UUserWidget* _sniperUI;

	//탄환 파편 팩토리
	UPROPERTY(EditAnywhere, Category=BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;
	//크로스헤어 인스턴스
	UPROPERTY()
	class UUserWidget* _crosshairUI;
};
