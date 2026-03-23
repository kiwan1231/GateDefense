// Fill out your copyright notice in the Description page of Project Settings.


#include "FMathExtension.h"


namespace G1Extension
{
	FVector VectorDumpX(FVector vec)
	{
		vec.X = 0;
		return vec;
	}
	FVector VectorDumpY(FVector vec)
	{
		vec.Y = 0;
		return vec;
	}
	FVector VectorDumpZ(FVector vec)
	{
		vec.Z = 0;
		return vec;
	}
}