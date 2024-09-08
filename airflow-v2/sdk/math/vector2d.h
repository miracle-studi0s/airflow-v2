#pragma once

class vector2d
{
private:
	float x;
	float y;

public:
	vector2d();
	vector2d(float x, float y);
	vector2d(const vector2d& other);
	vector2d(vector2d&& other) noexcept;
	vector2d(float* other);

	float get_x();
	float get_y();

	void set_x(float x);
	void set_y(float y);

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

	bool operator==(const vector2d& other);
	bool operator!=(const vector2d& other);

	float length_sqr();
	float length();

	vector2d normalized();
};