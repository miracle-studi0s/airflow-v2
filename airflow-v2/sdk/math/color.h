#pragma once

#include <array>
#include <cmath>
#include <imgui/imgui.h>

class c_byte_color 
{
public:
	unsigned char r, g, b;

	c_byte_color(float _r = 0, float _g = 0, float _b = 0);

	c_byte_color operator+(c_byte_color color);
	c_byte_color operator+(unsigned char n);
	c_byte_color operator+=(c_byte_color color);
	c_byte_color operator+=(unsigned char n);
	c_byte_color operator-(c_byte_color color);
	c_byte_color operator-(unsigned char n);
	c_byte_color operator-=(c_byte_color color);
	c_byte_color operator-=(unsigned char n);
	c_byte_color operator/(c_byte_color color);
	c_byte_color operator/(unsigned char n);
	c_byte_color operator/=(c_byte_color color);
	c_byte_color operator/=(unsigned char n);
	c_byte_color operator*(c_byte_color color);
	c_byte_color operator*(unsigned char n);
	c_byte_color operator*=(c_byte_color color);
	c_byte_color operator*=(unsigned char n);
	bool operator==(c_byte_color color);
	bool operator!=(c_byte_color color);
};

class c_color
{
public:
	float r, g, b, a;

	c_color(float _r = 0, float _g = 0, float _b = 0, float _a = 0);
	c_color operator+(c_color color);
	c_color operator+(float n);
	c_color operator+=(c_color color);
	c_color operator+=(float n);
	c_color operator-(c_color color);
	c_color operator-(float n);
	c_color operator-=(c_color color);
	c_color operator-=(float n);
	c_color operator/(c_color color);
	c_color operator/(float n);
	c_color operator/=(c_color color);
	c_color operator/=(float n);
	c_color operator*(c_color color);
	c_color operator*(float n);
	c_color operator*=(c_color color);
	c_color operator*=(float n);
	bool operator==(c_color color);
	bool operator!=(c_color color);
	c_color convert_from_hsv_to_color();
	c_color lerp(c_color& other, float step);
	c_byte_color to_byte();
	c_color set_alpha(float alpha);
	ImColor im();
};