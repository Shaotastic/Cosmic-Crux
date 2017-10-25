#pragma once

//Keeps track of elapsed time to use for things like physics calculations
class Timer
{
public:
	Timer();
	~Timer();

	float tick();
	float getElapsedTimeMS();
	float getElapsedTimeS();
	float getCurrentTime();

private:
	float currentTime, previousTime, elapsedTime;

};