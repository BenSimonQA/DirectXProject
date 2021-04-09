#include "GameTime.h"

namespace Library
{
	GameTime::GameTime()
		: mTotalGameTime(0.0), mElapsedGameTime(0.0)
	{
	}

	int GameTime::TotalGameTime() const
	{
		if (mTotalGameTime >= 60)
		{
			return 60;
		}
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(int totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	double GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(double elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}