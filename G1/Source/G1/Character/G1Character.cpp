// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"
#include "AbilitySystem/G1AbilitySystem.h"

// Sets default values
AG1Character::AG1Character()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AG1Character::BeginPlay()
{
	Super::BeginPlay();
	
	AddCharacterAbilities();
}

// Called every frame
void AG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AG1Character::HandleGameplayEvent(FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	
}

// Called to bind functionality to input
void AG1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AG1Character::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AG1Character::InitAbilitySystem()
{
}

void AG1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}
void AG1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AG1Character::AddCharacterAbilities()
{
	UG1AbilitySystem* AS = Cast<UG1AbilitySystem>(AbilitySystem);
	if (AS == nullptr)
	{
		return;
	}

	AS->AddCharacterAbilities(StartupAbilities);
}

void AG1Character::ActivateAbility(FGameplayTag AbilityTag)
{
	if (AbilitySystem)
		AbilitySystem->ActivateAbility(AbilityTag);
}

bool AG1Character::IsAttackState()
{
	return State == ECharacterState::MoveAttack;
}

