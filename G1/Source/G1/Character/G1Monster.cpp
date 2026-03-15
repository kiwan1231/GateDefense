// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Monster.h"
#include "AbilitySystem/Attributes/G1MonsterSet.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "Components/BoxComponent.h"
#include "Character/G1Player.h"

AG1Monster::AG1Monster()
	: Super()
{
	TeamTag = G1GameplayTags::Team_Monster;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AbilitySystem = CreateDefaultSubobject<UG1AbilitySystem>("AbilitySystem");

	AttributeSet = CreateDefaultSubobject<UG1MonsterSet>("MonsterSet");

	//RHandHitBox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("R_Hand_HitBox")));
	//RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	//LHandHitBox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("L_Hand_HitBox")));
	//LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);



	/*RHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RHandHitBox"));
	RHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_r"));
	RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	LHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LHandHitBox"));
	LHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_l"));
	LHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);*/

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
	AG1Player* demagedPlayer = Cast<AG1Player>(OtherActor);
	if (demagedPlayer == nullptr || demagedPlayer->State == ECharacterState::Dead)
	{
		return;
	}

	if (OverlappedComponent == RHandHitBox || OverlappedComponent == LHandHitBox)
	{
		demagedPlayer->OnDamaged(AttributeSet->GetBaseDamage(), Cast<AG1Character>(this));
	}
}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();

	TArray<UBoxComponent*> Boxes;
	GetComponents<UBoxComponent>(Boxes);

	for (UBoxComponent* Box : Boxes)
	{
		if (Box->GetName() == TEXT("R_Hand_HitBox"))
		{
			RHandHitBox = Box;
			RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);
			RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else if (Box->GetName() == TEXT("L_Hand_HitBox"))
		{
			LHandHitBox = Box;
			LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);
			LHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
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

	/*const FGameplayTag AttackTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack"));

	if (EventTag.MatchesTagExact(AttackTag))
	{
	}*/

	if (EventType == ECharacterAnimNotiType::OnQueryOnly)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (EventType == ECharacterAnimNotiType::NoCollision)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
