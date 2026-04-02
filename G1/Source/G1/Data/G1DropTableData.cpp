#include "Data/G1DropTableData.h"
#include "Math/UnrealMathUtility.h"

const TArray<FG1DropEntry>* UG1DropTableData::FindDropEntries(const FName& MonsterDropID) const
{
	for (const FMonsterDropRow& Row : DropTable)
	{
		if (Row.MonsterDropID == MonsterDropID)
		{
			return &Row.DropEntries;
		}
	}
	return nullptr;
}

void UG1DropTableData::RollDrops(const FName& MonsterDropID, TArray<FG1DropResult>& OutResults, float RandomSeed) const
{
	OutResults.Reset();

	const TArray<FG1DropEntry>* Entries = FindDropEntries(MonsterDropID);
	if (Entries == nullptr || Entries->Num() == 0)
	{
		return;
	}

	// 시드 고정이 필요하면 지정(디버깅용), 기본은 엔진 랜덤
	if (RandomSeed >= 0.0f)
	{
		FMath::SRandInit(static_cast<int32>(RandomSeed));
	}

	for (const FG1DropEntry& Entry : *Entries)
	{
		// DropChance 기반 판정
		const float RandomValue = FMath::FRand(); // 0..1
		if (RandomValue <= Entry.DropChance)
		{
			FG1DropResult Result;
			Result.ItemID = Entry.ItemID;
			// 개수 결정
			if (Entry.MaxCount <= Entry.MinCount)
			{
				Result.Count = Entry.MinCount;
			}
			else
			{
				Result.Count = FMath::RandRange(Entry.MinCount, Entry.MaxCount);
			}

			// 유효 개수만 추가
			if (Result.Count > 0)
			{
				OutResults.Add(Result);
			}
		}
	}
}