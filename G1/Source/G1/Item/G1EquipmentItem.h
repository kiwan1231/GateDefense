// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/G1Item3DInstance.h"
#include "G1EquipmentItem.generated.h"

UCLASS()
class G1_API AG1EquipmentItem : public AG1Item3DInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AG1EquipmentItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	class UBoxComponent* CollisionBox;

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<class AG1Character> ownerCharacter;

public:
	UPROPERTY(BlueprintReadWrite, Category = Ability)
	TArray<TSubclassOf<class UGameplayAbility>> ItemAbilities;

public:
	UPROPERTY(BlueprintReadOnly)
	FName ItemID;

	UPROPERTY()
	TSet<AActor*> HitActors;

	FVector PrevLocation;
	FQuat   PrevRotation;
	bool bIsAttacking;

public:
	void InitEquipment(FName _ItemID);
	void SetOwner(class AG1Character* owner);
	void SetWeaponCollisionEnabled(bool Enabled);

private:
	UFUNCTION()
	void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PerformAttackTrace();
};