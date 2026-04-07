// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/G1DropItem.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "UI/Item/DropItem/G1DropItemNameWidget.h"

// Sets default values
AG1DropItem::AG1DropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	RootPrimComponent = nullptr;
	bHasLanded = false;

	// 기본 파라미터 (작게 튀도록 설정)
	LaunchUpImpulseMin = 250.f;
	LaunchUpImpulseMax = 450.f;

	LaunchHorizontalImpulseMin = 80.f;
	LaunchHorizontalImpulseMax = 200.f;

	GroundNormalZThreshold = 0.6f;
	bDisablePhysicsOnLanded = true;

	LandOffsetFromGround = 1.0f;

	UiRootScene = CreateDefaultSubobject<USceneComponent>(TEXT("UIRootScene"));
	NameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidgetComponent"));
	if (UiRootScene)
	{
		NameWidgetComponent->SetupAttachment(UiRootScene);
	}
	else
	{
		NameWidgetComponent->SetupAttachment(GetRootComponent());
	}
}

// Called when the game starts or when spawned
void AG1DropItem::BeginPlay()
{
	Super::BeginPlay();

	if (NameWidgetComponent)
	{
		NameWidgetComponent->SetWidgetClass(NameWidgetClass);
		NameWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		NameWidgetComponent->SetDrawSize(FVector2D(200, 40));
		NameWidgetComponent->SetDrawAtDesiredSize(true);
		NameWidgetComponent->SetRelativeLocation(FVector(0, 0, 100));
	}
	
	/*
	// 루트 컴포넌트를 프리미티브로 캐스트하여 물리/충돌 처리 준비
	RootPrimComponent = Cast<UPrimitiveComponent>(GetRootComponent());
	if (RootPrimComponent)
	{
		// 충돌 이벤트 수신 허용
		RootPrimComponent->SetNotifyRigidBodyCollision(true);

		// 물리 시뮬레이션 활성화(아이템이 물리 기반이라면)
		if (!RootPrimComponent->IsSimulatingPhysics())
		{
			RootPrimComponent->SetSimulatePhysics(true);
		}
		RootPrimComponent->SetEnableGravity(true);

		// 히트 콜백 바인딩
		RootPrimComponent->OnComponentHit.AddDynamic(this, &AG1DropItem::OnRootComponentHit);

		// 랜덤한 수평 방향 생성 (동서남북 포함)
		const float AngleDeg = FMath::FRandRange(0.f, 360.f);
		const float AngleRad = FMath::DegreesToRadians(AngleDeg);
		const FVector HorizontalDir = FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.f).GetSafeNormal();

		// 임펄스 강도 랜덤화
		const float UpImpulse = FMath::FRandRange(LaunchUpImpulseMin, LaunchUpImpulseMax);
		const float HorImpulse = FMath::FRandRange(LaunchHorizontalImpulseMin, LaunchHorizontalImpulseMax);

		// 위쪽 성분 + 수평 성분의 합 (작은 폭발 느낌)
		const FVector TotalImpulse = FVector::UpVector * UpImpulse + HorizontalDir * HorImpulse;

		// 질량 고려한 임펄스 적용 (모든 축에서 부드러운 튕김)
		RootPrimComponent->AddImpulse(TotalImpulse, NAME_None, true);

		// 약간의 토크를 줘서 자연스러운 회전 추가 (옵션)
		const float Angular = FMath::FRandRange(-300.f, 300.f);
		RootPrimComponent->AddAngularImpulseInDegrees(FVector(Angular, Angular * 0.5f, Angular * 0.2f), NAME_None, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s BeginPlay: Root component is not a UPrimitiveComponent - fallback will try raycast landing"), *GetName());
	}
	*/
}

// Called every frame
void AG1DropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	return;

	// 루트가 프리미티브가 아니고 아직 착지하지 않은 경우, 안전하게 라인트레이스로 착지 체크
	/*if (!bHasLanded && RootPrimComponent == nullptr)
	{
		FVector Start = GetActorLocation();
		FVector End = Start - FVector(0.f, 0.f, 300.f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
		{
			HandleLanded(Hit);
		}
	}*/
}

void AG1DropItem::SetDropItem(FName DropItemID)
{
	ItemID = DropItemID;

	if (NameWidgetComponent == nullptr)
	{
		return;
	}

	if (UG1DropItemNameWidget* NameWidget = Cast<UG1DropItemNameWidget>(NameWidgetComponent->GetUserWidgetObject()))
	{
		NameWidget->SetItem(ItemID);
	}
}

void AG1DropItem::OnRootComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHasLanded)
	{
		return;
	}

	// 충돌 법선의 Z 성분으로 바닥인지 판단 (평지에 가까울수록 Z가 큼)
	/*const float ImpactZ = Hit.ImpactNormal.Z;
	if (ImpactZ >= GroundNormalZThreshold)
	{
		HandleLanded(Hit);
	}*/
	// 바닥이 아닐 경우(벽 등)에는 별도 처리 없이 물리 반응에 맡김
}

void AG1DropItem::HandleLanded(const FHitResult& Hit)
{
	bHasLanded = true;

	// 착지 지점으로 위치 보정 (작은 오프셋 포함)
	FVector LandLocation = Hit.ImpactPoint + Hit.ImpactNormal * LandOffsetFromGround;

	// 로그(Debugging)
	UE_LOG(LogTemp, Log, TEXT("%s landed at %s (normal Z = %.3f)"), *GetName(), *LandLocation.ToString(), Hit.ImpactNormal.Z);

	SetActorLocation(LandLocation);

	// 물리 비활성화(옵션)
	if (RootPrimComponent && bDisablePhysicsOnLanded)
	{
		RootPrimComponent->SetSimulatePhysics(false);
		RootPrimComponent->SetEnableGravity(false);
		// 충돌은 그대로 두어 플레이어가 줍도록 허용
	}

	// (선택) 착지 시 이펙트나 사운드 재생 지점
	// 예: UGameplayStatics::SpawnEmitterAtLocation(...) 등
}