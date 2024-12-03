// UhuMovementDataAsset.cpp
// Copyright by MykeUhu

#include "Data/UhuMovementDataAsset.h"

FMovementSpeedLevel UUhuMovementDataAsset::GetSpeedLevelForIndex(int32 Index) const
{
	if (SpeedLevels.IsValidIndex(Index))
	{
		return SpeedLevels[Index];
	}
	return FMovementSpeedLevel();
}

