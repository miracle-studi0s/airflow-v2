#pragma once

struct ImVec2;

class vector2d
{
public:
	float x;
	float y;

	vector2d();
	vector2d(float x, float y);
	vector2d(const vector2d& other);
	vector2d(vector2d&& other) noexcept;
	vector2d(float* other);

	vector2d operator+(const vector2d& other);
	vector2d operator-(const vector2d& other);
	vector2d operator*(const vector2d& other);
	vector2d operator/(const vector2d& other);

	vector2d operator+=(const vector2d& other);
	vector2d operator-=(const vector2d& other);
	vector2d operator*=(const vector2d& other);
	vector2d operator/=(const vector2d& other);

	vector2d operator+=(float value);
	vector2d operator-=(float value);
	vector2d operator*=(float value);
	vector2d operator/=(float value);

	vector2d operator=(const vector2d& other);
	vector2d operator=(vector2d&& other) noexcept;

	vector2d operator=(const ImVec2& other);
	vector2d operator=(ImVec2&& other) noexcept;

	bool operator==(const vector2d& other);
	bool operator!=(const vector2d& other);

	float length_sqr();
	float length();

	vector2d normalized();
};