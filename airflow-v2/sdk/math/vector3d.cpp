#include <cmath>
#include <limits>

#include "../protobuf/cs_user_cmd.pb.h"
#include "vector3d.h"

vector3d::vector3d() : x(0.f), y(0.f), z(0.f) {}
vector3d::vector3d(float x, float y, float z) : x(x), y(y), z(z) {}

vector3d::vector3d(const CMsgQAngle& other) : x(other.x()), y(other.y()), z(other.z()) {}

vector3d::vector3d(const vector3d& other) : x(other.x), y(other.y), z(other.z) {}
vector3d::vector3d(vector3d&& other) noexcept : x(other.x), y(other.y), z(other.z) {}

vector3d::vector3d(float* other) : x(other[0]), y(other[1]), z(other[2]) {}

vector3d vector3d::operator+(const vector3d& other)
{
	return { x + other.x, y + other.y, z + other.z };
}

vector3d vector3d::operator-(const vector3d& other)
{
	return { x - other.x, y - other.y, z - other.z };
}

vector3d vector3d::operator*(const vector3d& other)
{
	return { x * other.x, y * other.y, z * other.z };
}

vector3d vector3d::operator/(const vector3d& other)
{
	return { x / other.x, y / other.y, z / other.z };
}

vector3d vector3d::operator+=(const vector3d& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vector3d vector3d::operator-=(const vector3d& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vector3d vector3d::operator*=(const vector3d& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vector3d vector3d::operator/=(const vector3d& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

vector3d vector3d::operator+=(float value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

vector3d vector3d::operator-=(float value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

vector3d vector3d::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

vector3d vector3d::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

vector3d vector3d::operator+(float value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

vector3d vector3d::operator-(float value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

vector3d vector3d::operator*(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

vector3d vector3d::operator/(float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

vector3d vector3d::operator=(const vector3d& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

vector3d vector3d::operator=(vector3d&& other) noexcept
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool vector3d::operator==(const vector3d& other)
{
	return x == other.x
		&& y == other.y
		&& z == other.z;
}

bool vector3d::operator!=(const vector3d& other)
{
	return x != other.x
		|| y != other.y
		|| z != other.z;
}

float vector3d::length_sqr()
{
	return x * x + y * y + z * z;
}

float vector3d::length()
{
	return std::sqrtf(length_sqr());
}

float vector3d::length_2d_sqr()
{
	return x * x + y * y;
}

float vector3d::length_2d()
{
	return std::sqrtf(length_2d_sqr());
}

float vector3d::dot_product(const vector3d& other)
{
	return x * other.x + y * other.y + z * other.z;
}

float vector3d::dot_product(float* other)
{
	return x * other[0] + y * other[1] + z * other[2];
}

float vector3d::inversed_dot(const vector3d& other)
{
	return x * other.y + y * other.x + z * other.z;
}

vector3d vector3d::cross_product(const vector3d& other)
{
	return 
	{	
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

vector3d vector3d::normalized()
{
	float vector_length = length() + std::numeric_limits<float>::epsilon();

	x /= vector_length;
	y /= vector_length;
	z /= vector_length;

	return *this;
}