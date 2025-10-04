
#ifndef VECTOR2_LOADED
#define VECTOR2_LOADED

#include <cmath>
#include <iostream>
#include <memory>

/** Features logic of a 2-dimenional vector, which lives on a XY coordinate plane
 ** described by the `Plane` class. */
class Vector2 final
{
private:
	static const float DEG_2_RAD;

public:
	float x;
	float y;

	static const Vector2 ZERO;
	static const Vector2 ONE;
	static const Vector2 RIGHT;
	static const Vector2 DOWN;
	static const Vector2 LEFT;
	static const Vector2 UP;

	/** Returns the right vector [1 0] rotated clockwisely by `angleDeg` degrees. */
	static Vector2 towards(float angleDeg);

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	Vector2 operator=(const Vector2& other);
	bool    operator==(const Vector2& other) const;
};

Vector2 operator*(float scalar, const Vector2& other);  // Allow multiplication commutativity.
std::ostream& operator<<(std::ostream& os, const Vector2& v);
std::istream& operator>>(std::istream& is, Vector2& v);

#endif
