// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "G1CharacterDefine.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "Interface/G1HighlightInterface.h"

//#include "Delegates/Delegate.h"
//#include "Delegates/DelegateCombinations.h"

#include "G1Character.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterDead, AG1Character*);

UCLASS()
class G1_API AG1Character : public ACharacter, public IAbilitySystemInterface, public IG1HighlightInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AG1Character();

public: /// ReadWrite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterState State = ECharacterState::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TeamTag;

protected: /// ReadOnly
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Ability)
	TObjectPtr<class UG1AbilitySystem> AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability)
	TObjectPtr<class UG1AttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category =Ability)
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equip)
	TArray<FName> EquipmentList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equip)
	TMap<FName, TObjectPtr<class AG1EquipmentItem>> EquipObjectList;

	UPROPERTY()
	TArray<struct FG1CharacterConditionData> ConditionDataList;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UG1AnimInstance> AnimInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleGameplayEvent(class UAnimMontage* Montage, FGameplayTag EventTag, ECharacterAnimNotiType EventType);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:/// ability
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker);
	virtual void OnDead(TObjectPtr<AG1Character> Attacker);

public: // equipment
	void InitEquipment();
	virtual void AddEquipment(const FName EquipID);
	virtual void RemoveEquipment(const FName EquipID);

public: // ConditionData
	virtual void UpdateConditionData(float DeltaTime);
	virtual void AddConditionData(EConditionType Type, float DurationTime, float Value1);

public: // interface
	virtual void InitAbilitySystem();
	virtual void Highlight();
	virtual void UnHighlight();

public: /// public ±â´É ÇÔ¼ö

	// ¾îºô¸®Æ¼ ½Àµæ
	void AddCharacterAbilities();
	// ¾îºô¸®Æ¼ ½ÇÇà
	void ActivateAbility(FGameplayTag AbilityTag);

public:
	bool IsSameTeam(const AActor* Ohter) const;
	bool IsEnemyTeam(const AActor* Ohter) const;
	float TotalDemage() const;
	
public:
	void SetSatate(ECharacterState _State);
	bool InAttackState() const;
	bool InAbilityState() const;
	bool InDeadState() const;

public:
	virtual bool EnableMove() const;
	virtual bool EnableJump() const;
	virtual bool EnableAttack() const;
	virtual bool EnableAbility() const;

private:
	void G1PlayAnimMontage(class UAnimMontage* Montage);

public:
	FOnCharacterDead OnCharacterDead;
};
