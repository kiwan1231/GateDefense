// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/G1Item3DInstance.h"
#include "Components/PrimitiveComponent.h"
#include "G1DropItem.generated.h"

UCLASS()
class G1_API AG1DropItem : public AG1Item3DInstance
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AG1DropItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 루트 프리미티브 컴포넌트가 충돌했을 때 호출되는 콜백
	UFUNCTION()
	void OnRootComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 착지 처리를 담당
	void HandleLanded(const FHitResult& Hit);

	// 루트 프리미티브 캐시
	UPROPERTY()
	UPrimitiveComponent* RootPrimComponent;

	// 착지 플래그
	UPROPERTY(Transient)
	bool bHasLanded;

	UPROPERTY(BlueprintReadOnly)
	FName ItemID;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDropItem(FName DropItemID);

protected:


	// 위로 솟구치는 임펄스 범위
	UPROPERTY(EditAnywhere, Category = "Drop|Launch")
	float LaunchUpImpulseMin;

	UPROPERTY(EditAnywhere, Category = "Drop|Launch")
	float LaunchUpImpulseMax;

	// 수평 임펄스 세기 범위 (작은 값으로 살짝 튀게)
	UPROPERTY(EditAnywhere, Category = "Drop|Launch")
	float LaunchHorizontalImpulseMin;

	UPROPERTY(EditAnywhere, Category = "Drop|Launch")
	float LaunchHorizontalImpulseMax;

	// 착지으로 판단할 때 법선의 Z 임계값 (1에 가까울수록 평지에만 착지로 판단)
	UPROPERTY(EditAnywhere, Category = "Drop|Detect")
	float GroundNormalZThreshold;

	// 착지 시 물리 시뮬레이션을 끌지 여부
	UPROPERTY(EditAnywhere, Category = "Drop|Behavior")
	bool bDisablePhysicsOnLanded;

	// 착지 후 약간 위치 보정할 오프셋 거리
	UPROPERTY(EditAnywhere, Category = "Drop|Behavior")
	float LandOffsetFromGround;

	// 드랍(픽업)용 액터 클래스 ? 월드에 떠있는 픽업을 위한 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UG1DropItemNameWidget> NameWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UWidgetComponent> NameWidgetComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class USceneComponent> UiRootScene;
};
