// UhuMovementDataAsset.cpp
// Copyright by MykeUhu

#include "Data/UhuMovementDataAsset.h"

FMovementSpeedLevel UUhuMovementDataAsset::GetSpeedLevelForTag(FGameplayTag SpeedTag) const
{
	for (const FMovementSpeedLevel& SpeedLevel : SpeedLevels)
	{
		if (SpeedLevel.SpeedTag == SpeedTag)
		{
			return SpeedLevel;
		}
	}
	return FMovementSpeedLevel();
}