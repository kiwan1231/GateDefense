// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/G1GameModeData.h"

const FEventData* UG1GameModeData::FindEventData(const FName& EventID) const
{
    for (const FEventData& Data : EventDataList)
    {
        if (Data.EventID.IsEqual(EventID))
        {
            return &Data;
        }
    }

    return nullptr;
}

