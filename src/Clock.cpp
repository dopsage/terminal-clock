
#include "Clock.hpp"

const int Clock::STEPS_PER_DP = 10;

std::time_t Clock::getEpochTime()
{
	std::chrono::time_point tpNow = std::chrono::system_clock::now();
	std::time_t sNow = std::chrono::system_clock::to_time_t(tpNow);
	return sNow;
}

Clock::Clock(uint8_t diameter) : radius(diameter / 2.0f), safeRadius(diameter / 2.0f - 0.5f), Plane(diameter, diameter)
{
	update();
}

void Clock::update()
{
	set(' ');  // Clear the plane.

	/*** DRAW AN OUTER CIRCLE INCLUDING HOUR INDICATORS ***/

	// First do the outer circle.
	int   stepCount       = 2 * 3.141593f * radius * STEPS_PER_DP;
	float stepValue       = 360.0f / stepCount;
	float currentAngleDeg = 0.0f;
	std::vector<std::pair<Vector2, int>> hourIndicators;
	for(int stepIndex = 0; stepIndex < stepCount - 1; stepIndex++)  // -1 to not reach exact full angle!
	{
		Vector2 coord = radius * Vector2::ONE + safeRadius * Vector2::towards(270.0f + currentAngleDeg);

		// Adjust data point looks to the current drawing angle.
		DataPoint dp { '/', '#' };
		     if( (currentAngleDeg > 337.5f && currentAngleDeg < 360.0f ) ||
		         (currentAngleDeg > 0.0f   && currentAngleDeg < 22.5f  ) ||
			     (currentAngleDeg > 157.5f && currentAngleDeg < 202.5f))
			 dp.left = '=';
		else if( (currentAngleDeg > 22.5f  && currentAngleDeg < 67.5f )  ||
				 (currentAngleDeg > 202.5f && currentAngleDeg < 247.5f))
			 dp.left = '\\';
		else if( (currentAngleDeg > 67.5f  && currentAngleDeg < 112.5f ) ||
				 (currentAngleDeg > 247.5f && currentAngleDeg < 292.5f))
			 dp.left = '|';

		// Save coordinate-to-hour mapping for later.
		if((int)currentAngleDeg % 30 == 0)
		{
			int hour = (int)currentAngleDeg / 30;
			hourIndicators.push_back(std::make_pair(coord, hour ? hour : 12));
		}

		// Draw part of the circle at coordinate and move on.
		set(coord, dp);
		currentAngleDeg += stepValue;
	}
	// Second do the hour indicators using cached data.
	for(const auto& hi : hourIndicators)
	{
		set(hi.first, {
			(uint8_t)(0x30 + hi.second / 10),
			(uint8_t)(0x30 + hi.second % 10)
		});
	}

	/*** DRAW CLOCK HANDS ***/

	// Obtain current hour, minute and second for the local timezone.
	std::time_t sNow      = getEpochTime();
    std::tm*    localTime = std::localtime(&sNow);
    int hour   = localTime->tm_hour % 12;  // Clock supports only 12 hours.
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    /* Prepare hand direction vectors. Hands are influenced by the current time differently:
     * Hour hand   - hour, minute and second add 30, 30/60=1/2 and 30/60/60=1/120 degrees.
     * Minute hand - minute and second add 6 and 6/60=1/10 degrees.
     * Second hand - second add 6 degrees. */
    Vector2 handDirections[3] = {
    	Vector2::towards(270.0f + (30.0f * hour)   + (minute / 2.0f ) + (second / 120.0f)),  // Hour hand.
    	Vector2::towards(270.0f + (6.0f  * minute) + (second / 10.0f)),						 // Minute hand.
    	Vector2::towards(270.0f + (6.0f  * second))											 // Second hand.
    };
    DataPoint handStyles[3] = {
    	{ '@', '@' },
    	{ '$', '$' },
    	{ '^', '^' }
    };
    for(int handIndex = 0; handIndex < 3; handIndex++)
    {
    	// Hand lengths function: f(i)=(7/30)*(i+1)+0.2, where i - hand index from set {0, 1, 2}.
    	float handLength 	 = safeRadius * ((handIndex + 1) * 7.0f / 30.0f + 0.2f);
    	float centerDistance = 0.0f;
    		  stepCount 	 = handLength * STEPS_PER_DP;
    		  stepValue      = handLength / stepCount;
    	for(int stepIndex = 0; stepIndex < stepCount; stepIndex++)
    	{
    		set(radius * Vector2::ONE + centerDistance * handDirections[handIndex], handStyles[handIndex]);
    		centerDistance += stepValue;
    	}
    }
}
