
#include "Vector2.hpp"

const float Vector2::DEG_2_RAD = 0.017453f;

const Vector2 Vector2::ZERO  = Vector2( 0.0f,  0.0f);

const Vector2 Vector2::ONE   = Vector2( 1.0f,  1.0f);

const Vector2 Vector2::RIGHT = Vector2( 1.0f,  0.0f);

const Vector2 Vector2::DOWN  = Vector2( 0.0f,  1.0f);

const Vector2 Vector2::LEFT  = Vector2(-1.0f,  0.0f);

const Vector2 Vector2::UP    = Vector2( 0.0f, -1.0f);

Vector2 Vector2::towards(float angleDeg)
{
	return Vector2(cosf(angleDeg * DEG_2_RAD), sinf(angleDeg * DEG_2_RAD));
}

Vector2::Vector2() : x(0.0f), y(0.0f)
{

}

Vector2::Vector2(float x, float y) : x(x), y(y)
{

}

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y)
{
	
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(this->x / scalar, this->y / scalar);
}

Vector2 Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return this->x == other.x && this->y == other.y;
}

Vector2 operator*(float scalar, const Vector2& other)
{
	return other.operator*(scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
	return os << "[ " << v.x << " " << v.y << " ]";
}

std::istream& operator>>(std::istream& is, Vector2& v)
{
	return is >> v.x >> v.y;
}
