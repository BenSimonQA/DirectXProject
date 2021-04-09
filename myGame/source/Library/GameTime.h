#pragma once

namespace Library
{
	class GameTime
	{
	public:
		GameTime();

		int TotalGameTime() const;
		void SetTotalGameTime(int totalGameTime);

		double ElapsedGameTime() const;
		void SetElapsedGameTime(double elapsedGameTime);

	private:
		double mTotalGameTime;
		double mElapsedGameTime;
	};
}
