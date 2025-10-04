
#ifndef CLOCK_LOADED
#define CLOCK_LOADED

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "Vector2.hpp"
#include "Plane.hpp"

/** Manages drawing of an analog clock by utilizing `Plane` class. Clock is outputed to the standard output stream
 ** `cout`, and can be updated using dedicated method. */
class Clock : protected Plane
{
private:
	const static int STEPS_PER_DP;  // Drawing steps done per single plane's data point.

	float radius;
	float safeRadius;  // Decreased radius prevents from drawing outside the plane range due to flooring imperfection.

public:
	using Plane::show;  // Promotes derived `show` from protected to public.

	/** Returns amount of seconds that passed since epoch (01.01.1970). */
	static std::time_t getEpochTime();

	/** Constructs a new clock, and immediatelly calls `update` method. */
	Clock(uint8_t diameter);

	/** Redraws the whole clock (outer circle, and hands), so it depicts the time it is drawn again at. */
	void update();
};

#endif
