
#ifndef PLANE_LOADED
#define PLANE_LOADED

#include <iostream>
#include <memory>
#include "Vector2.hpp"

struct DataPoint
{
	uint8_t left;
	uint8_t right;
};

/** Provides functionality of a coordinate plane, and allows to visualize it using textual graphics.
 ** There are two coordinates: horizontal (X) and vertical (Y); their pair (X, Y) uniquely identifies a data point.
 ** The top-left corner of the plane is (0, 0). X grows to the right, and Y to the bottom. */
class Plane
{
private:
	ushort  				bufferLength;
	uint8_t 				bufferWidth;
	uint8_t 				planeHeight;
	uint8_t 				planeWidth;
	std::unique_ptr<char[]> buffer;
	std::ostream* 			receiver;

public:
	/** Constructs a new plane with size of `width` by `height` data points.
	 ** Plane visualization is done by writing the plane buffer to the output stream `receiver`. */
	Plane(uint8_t width, uint8_t height, std::ostream& receiver = std::cout);

	/** Destructs the plane instance, even if the instance is interpreted as the derived class. */
	virtual ~Plane() = default;

	/** Returns data point stored at (`x`, `y`), or at vector `v`. */
	DataPoint get(int x,   int y);
	DataPoint get(float x, float y);
	DataPoint get(Vector2 v);

	/** Returns height of the plane. */
	uint8_t height();

	/** Returns width of the plane. */
	uint8_t width();

	/** Stores data point at every possible data point. */
	void set(DataPoint dp);
	void set(uint8_t   data);
	
	/** Stores data point at (`x`, `y`), or at vector `v`. */
	void set(int     x, int       y, DataPoint dp);
	void set(float   x, float     y, DataPoint dp);
	void set(Vector2 v, DataPoint dp);
	void set(int     x, int       y, uint8_t   data);
	void set(float   x, float     y, uint8_t   data);
	void set(Vector2 v, uint8_t   data);

	/** Writes the plane buffer to the output stream provided in constructor. */
	void show();
};

#endif
