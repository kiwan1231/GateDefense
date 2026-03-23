// Fill out your copyright notice in the Description page of Project Settings.


#include "G1Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Player/G1PlayerState.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "AbilitySystem/Attributes/G1AttributeSet.h"
#include "AbilitySystem/Attributes/G1PlayerSet.h"

// Sets default values
AG1Player::AG1Player()
	: Super()
{
	TeamTag = G1GameplayTags::Team_Player;

	/// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0, 0));
	SpringArm->SocketOffset = FVector(0.f, 0.f, 20.f);
	SpringArm->TargetOffset = FVector(0.f, 0.f, 50.f);
	SpringArm->TargetArmLength = 250.f;
	SpringArm->bUsePawnControlRotation = false;

	/// 벽 충돌 카메라 처리
	SpringArm->bDoCollisionTest = false;
	SpringArm->ProbeSize = 12.f;
	SpringArm->ProbeChannel = ECC_Camera;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	CameraPivotSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CameraPivotSphere"));
	CameraPivotSphere->SetupAttachment(GetCapsuleComponent());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void AG1Player::BeginPlay()
{
	Super::BeginPlay();

	SpringArmTargetOffset = SpringArm->TargetOffset;
	SpringArmSocketOffset = SpringArm->SocketOffset;
	CameraPivotSphere->SetWorldLocation(GetSpringArmEndLocation());
}

void AG1Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}

// Called every frame
void AG1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCamera(DeltaTime);
}

// Called to bind functionality to input
void AG1Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AG1Player::HandleGameplayEvent(FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	Super::HandleGameplayEvent(EventTag, EventType);
}

void AG1Player::UpdateCamera(float DeltaTime)
{
	FVector Start = GetActorLocation() + SpringArmTargetOffset;
	FVector End = CameraPivotSphere->GetComponentLocation();

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	float TargetPitch;

	if (bHit)
	{
		// 막힘 → 위에서 내려보게
		TargetPitch = -90.f; // 원하는 각도
	}
	else
	{
		// 정상 → 원래 각도
		TargetPitch = -35.f;
	}

	// 부드럽게 보간
	FRotator CurrentRot = SpringArm->GetRelativeRotation();
	FRotator TargetRot = FRotator(TargetPitch, CurrentRot.Yaw, 0.f);

	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, 5.f);

	SpringArm->SetRelativeRotation(NewRot);
}

void AG1Player::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	if (AG1PlayerState* PS = GetPlayerState<AG1PlayerState>())
	{
		AbilitySystem = Cast<UG1AbilitySystem>(PS->GetAbilitySystemComponent());
		AbilitySystem->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetG1PlayerSet();
	}
}

FVector AG1Player::GetSpringArmEndLocation()
{
	// 1. 시작 위치 (TargetOffset 포함됨)
	FVector Start = SpringArm->GetComponentLocation();

	// 2. 회전
	FRotator Rot = SpringArm->GetComponentRotation();

	// 3. SocketOffset (회전 적용)
	FVector Socket = Rot.RotateVector(SpringArm->SocketOffset);

	// 4. Arm 길이 (뒤로)
	FVector Backward = Rot.Vector() * -SpringArm->TargetArmLength;

	return Start + Socket + Backward;
}
