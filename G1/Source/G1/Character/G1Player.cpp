// Fill out your copyright notice in the Description page of Project Settings.


#include "G1Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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
	SpringArm->bDoCollisionTest = true;
	SpringArm->ProbeSize = 12.f;
	SpringArm->ProbeChannel = ECC_Camera;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void AG1Player::BeginPlay()
{
	Super::BeginPlay();
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
