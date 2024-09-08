#pragma once

class vector3d
{
private:
	float x;
	float y;
	float z;

public:
	vector3d();
	vector3d(float x, float y, float z);
	vector3d(const vector3d& other);
	vector3d(vector3d&& other) noexcept;
	vector3d(float* other);

	float get_x();
	float get_y();
	float get_z();

	void set_x(float x);
	void set_y(float y);
	void set_z(float z);

	vector3d operator+(const vector3d& other);
	vector3d operator-(const vector3d& other);
	vector3d operator*(const vector3d& other);
	vector3d operator/(const vector3d& other);

	vector3d operator+=(const vector3d& other);
	vector3d operator-=(const vector3d& other);
	vector3d operator*=(const vector3d& other);
	vector3d operator/=(const vector3d& other);

	vector3d operator+=(float value);
	vector3d operator-=(float value);
	vector3d operator*=(float value);
	vector3d operator/=(float value);

	vector3d operator=(const vector3d& other);
	vector3d operator=(vector3d&& other) noexcept;

	bool operator==(const vector3d& other);
	bool operator!=(const vector3d& other);

	float length_sqr();
	float length();

	float length_2d_sqr();
	float length_2d();

	float dot_product(const vector3d& other);
	float dot_product(float* other);

	vector3d cross_product(const vector3d& other);
	vector3d normalized();
};