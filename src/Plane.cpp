
#include "Plane.hpp"

Plane::Plane(uint8_t width, uint8_t height, std::ostream& receiver)
{
	this->bufferWidth  = 2 * width + 2;
	this->bufferLength = bufferWidth * height + 1;
	this->planeHeight  = height;
	this->planeWidth   = width;
	this->buffer 	   = std::make_unique<char[]>(bufferLength);
	this->receiver 	   = &receiver;
	
	// Set line terminators.
	for(int y = 0; y < height; y++)
	{
		int index 		= (bufferWidth - 2) + y * bufferWidth;
		buffer[index++] = ' ' ;
		buffer[index  ] = '\n';
	}

	// Set buffer terminator.
	buffer[bufferLength - 1] = '\0';

	set(' ');  // Initialize data points.
}

DataPoint Plane::get(int x, int y)
{
	return *((DataPoint*)&buffer[2 * x + y * bufferWidth]);
}
DataPoint Plane::get(float x, float y)
{
	return get((int)x, (int)y);
}
DataPoint Plane::get(Vector2 v)
{
	return get(v.x, v.y);
}

uint8_t Plane::height()
{
	return planeHeight;
}

uint8_t Plane::width()
{
	return planeWidth;
}

void Plane::set(DataPoint dp)
{
	for(int y = 0; y < planeHeight; y++)
	for(int x = 0; x < planeWidth ; x++)
		set(x, y, dp);
}
void Plane::set(uint8_t data)
{
	this->set({ data, data });
}

void Plane::set(int x, int y, DataPoint data)
{
	int index 		= 2 * x + y * bufferWidth;
	buffer[index++] = data.left;
	buffer[index  ] = data.right;
}
void Plane::set(float x, float y, DataPoint data)
{
	this->set((int)x, (int)y, data);
}
void Plane::set(Vector2 v, DataPoint data)
{
	this->set(v.x, v.y, data);
}
void Plane::set(int x, int y, uint8_t data)
{
	this->set(x, y, { data, data });
}
void Plane::set(float x, float y, uint8_t data)
{
	this->set((int)x, (int)y, { data, data });
}
void Plane::set(Vector2 v, uint8_t data)
{
	this->set(v.x, v.y, data);
}

void Plane::show()
{
	(*receiver) << buffer.get();
}
