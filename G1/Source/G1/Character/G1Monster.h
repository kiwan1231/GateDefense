// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/G1Character.h"

#include "G1Monster.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1Monster : public AG1Character
{
	GENERATED_BODY()
	
public:
	AG1Monster();

protected:
	UPROPERTY(BlueprintReadOnly)
	class UBoxComponent* RHandHitBox;
	UPROPERTY(BlueprintReadOnly)
	class UBoxComponent* LHandHitBox;

public:
	UPROPERTY(BlueprintReadOnly)
	FName MonsterDropID;

private:
	UFUNCTION()
	void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitAbilitySystem() override;

	virtual void HandleGameplayEvent(UAnimMontage* Montage, FGameplayTag EventTag, ECharacterAnimNotiType EventType);

	virtual void OnDead(TObjectPtr<AG1Character> Attacker) override;
};
