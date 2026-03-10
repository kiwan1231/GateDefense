// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Monster.h"
#include "AbilitySystem/Attributes/G1MonsterSet.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "Components/BoxComponent.h"

AG1Monster::AG1Monster()
	: Super()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AbilitySystem = CreateDefaultSubobject<UG1AbilitySystem>("AbilitySystem");

	AttributeSet = CreateDefaultSubobject<UG1MonsterSet>("MonsterSet");

	RHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RHandHitBox"));
	RHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_r"));
	RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	LHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LHandHitBox"));
	LHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_l"));
	LHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	//RHandHitBox->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	//RHandHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RHandHitBox->SetCollisionObjectType(ECC_WorldDynamic);
	//RHandHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//RHandHitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AG1Monster::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherActor->Implements<Interface>())
	{

	}*/

	if (OverlappedComponent == RHandHitBox)
	{
		UE_LOG(LogTemp, Log, TEXT("OnAttackOverlap RHandHitBox"));
	}
	else if (OverlappedComponent == LHandHitBox)
	{
		UE_LOG(LogTemp, Log, TEXT("OnAttackOverlap LHandHitBox"));
	}
}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
}

void AG1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	AbilitySystem->InitAbilityActorInfo(this, this);
}

void AG1Monster::HandleGameplayEvent(FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	Super::HandleGameplayEvent(EventTag, EventType);

	if (EventType == ECharacterAnimNotiType::OnQueryOnly)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (EventType == ECharacterAnimNotiType::NoCollision)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
