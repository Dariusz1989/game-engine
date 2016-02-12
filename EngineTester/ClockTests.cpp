#include <gtest\gtest.h>

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	sleep(1000);
	clock.newFrame();
	float timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.9f < timedTime && timedTime < 1.1f);
	clock.newFrame();
	sleep(500);
	clock.newFrame();
	timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.4f < timedTime);
	EXPECT_TRUE(timedTime < 0.6f);

	const int NUM_TESTS = 10 + rand() % 100;
	const float THRESHOLD = 0.1f;
	for (int i = 0; i < NUM_TESTS; i++)
	{
		int thisTestTimeMiliseconds = rand() % 10000;
		float thisTestTimeSeconds = thisTestTimeMiliseconds / 1000.0f;
		clock.newFrame();
		sleep(thisTestTimeMiliseconds);
		clock.newFrame();
		float elapsedSeconds = clock.timeElapsedLastFrame();
		EXPECT_TRUE((thisTestTimeSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE(elapsedSeconds < (thisTestTimeSeconds - THRESHOLD));
	}

	clock.timeElapsedLastFrame();
	EXPECT_TRUE(clock.shutdown());
}