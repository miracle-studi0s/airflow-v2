#include "color.h"

c_byte_color::c_byte_color(float _r, float _g, float _b)
	: r(static_cast<unsigned char>(_r)), g(static_cast<unsigned char>(_g)), b(static_cast<unsigned char>(_b)) {}

c_byte_color c_byte_color::operator+(c_byte_color color)
{
	return c_byte_color(r + color.r, g + color.g, b + color.b);
}

c_byte_color c_byte_color::operator+(unsigned char n)
{
	return c_byte_color(r + n, g + n, b + n);
}

c_byte_color c_byte_color::operator+=(c_byte_color color)
{
	r += color.r;
	g += color.g;
	b += color.b;

	return *this;
}

c_byte_color c_byte_color::operator+=(unsigned char n) 
{
	r += n;
	g += n;
	b += n;

	return *this;
}

c_byte_color c_byte_color::operator-(c_byte_color color)
{
	return c_byte_color(r - color.r, g - color.g, b - color.b);
}

c_byte_color c_byte_color::operator-(unsigned char n)
{
	return c_byte_color(r - n, g - n, b - n);
}

c_byte_color c_byte_color::operator-=(c_byte_color color) 
{
	r -= color.r;
	g -= color.g;
	b -= color.b;

	return *this;
}

c_byte_color c_byte_color::operator-=(unsigned char n)
{
	r -= n;
	g -= n;
	b -= n;

	return *this;
}

c_byte_color c_byte_color::operator/(c_byte_color color)
{
	return c_byte_color(r / color.r, g / color.g, b / color.b);
}

c_byte_color c_byte_color::operator/(unsigned char n)
{
	return c_byte_color(r / n, g / n, b / n);
}

c_byte_color c_byte_color::operator/=(c_byte_color color)
{
	r /= color.r;
	g /= color.g;
	b /= color.b;

	return *this;
}

c_byte_color c_byte_color::operator/=(unsigned char n)
{
	r /= n;
	g /= n;
	b /= n;

	return *this;
}

c_byte_color c_byte_color::operator*(c_byte_color color)
{
	return c_byte_color(r * color.r, g * color.g, b * color.b);
}

c_byte_color c_byte_color::operator*(unsigned char n)
{
	return c_byte_color(r * n, g * n, b * n);
}

c_byte_color c_byte_color::operator*=(c_byte_color color) 
{
	r *= color.r;
	g *= color.g;
	b *= color.b;

	return *this;
}

c_byte_color c_byte_color::operator*=(unsigned char n) 
{
	r *= n;
	g *= n;
	b *= n;

	return *this;
}

bool c_byte_color::operator==(c_byte_color color)
{
	return r == color.r && g == color.g && b == color.b;
}

bool c_byte_color::operator!=(c_byte_color color)
{
	return !(*this == color);
}

c_color::c_color(float _r, float _g, float _b, float _a) 
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

c_color::c_color(const c_color& other) 
	: r(other.r), g(other.g), b(other.b), a(other.a) {};

c_color::c_color(c_color&& other)
	: r(other.r), g(other.g), b(other.b), a(other.a) {};

c_color c_color::operator=(const c_color& other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return *this;
}

c_color c_color::operator+(c_color color)
{
	return c_color(r + color.r, g + color.g, b + color.b, a + color.a);
}

c_color c_color::operator+(float n)
{
	return c_color(r + n, g + n, b + n, a + n);
}

c_color c_color::operator+=(c_color color)
{
	r += color.r;
	g += color.g;
	b += color.b;
	a += color.a;

	return *this;
}

c_color c_color::operator+=(float n)
{
	r += n;
	g += n;
	b += n;
	a += n;

	return *this;
}

c_color c_color::operator-(c_color color)
{
	return c_color(r - color.r, g - color.g, b - color.b, a - color.a);
}

c_color c_color::operator-(float n)
{
	return c_color(r - n, g - n, b - n, a - n);
}

c_color c_color::operator-=(c_color color)
{
	r -= color.r;
	g -= color.g;
	b -= color.b;
	a -= color.a;

	return *this;
}

c_color c_color::operator-=(float n)
{
	r -= n;
	g -= n;
	b -= n;
	a -= n;

	return *this;
}

c_color c_color::operator/(c_color color)
{
	return c_color(r / color.r, g / color.g, b / color.b, a / color.a);
}

c_color c_color::operator/(float n)
{
	return c_color(r / n, g / n, b / n, a / n);
}

c_color c_color::operator/=(c_color color)
{
	r /= color.r;
	g /= color.g;
	b /= color.b;
	a /= color.a;

	return *this;
}

c_color c_color::operator/=(float n)
{
	r /= n;
	g /= n;
	b /= n;
	a /= n;

	return *this;
}

c_color c_color::operator*(c_color color)
{
	return c_color(r * color.r, g * color.g, b * color.b, a * color.a);
}

c_color c_color::operator*(float n)
{
	return c_color(r * n, g * n, b * n, a * n);
}

c_color c_color::operator*=(c_color color)
{
	r *= color.r;
	g *= color.g;
	b *= color.b;
	a *= color.a;

	return *this;
}

c_color c_color::operator*=(float n)
{
	r *= n;
	g *= n;
	b *= n;
	a *= n;

	return *this;
}

bool c_color::operator==(c_color color)
{
	return r == color.r && g == color.g && b == color.b && a == color.a;
}

bool c_color::operator!=(c_color color)
{
	return r != color.r || g != color.g || b != color.b || a != color.a;
}

c_color c_color::to_percent()
{
	r /= 255.f;
	g /= 255.f;
	b /= 255.f;
	a /= 255.f;
	return *this;
}

c_color c_color::lerp(c_color& other, float step)
{
	c_color lerped_color{
		std::lerp(r, other.r, step),
		std::lerp(g, other.g, step),
		std::lerp(b, other.b, step),
		std::lerp(a, other.a, step)
	};

	return lerped_color;
}

c_byte_color c_color::to_byte()
{
	return c_byte_color(r, g, b);
}

c_color c_color::set_alpha(float alpha)
{
	a = alpha;
	return c_color(r, g, b, a);
}

ImColor c_color::im()
{
	return ImColor(r, g, b, a);
}

uint32_t c_color::to_hex()
{
	return ((static_cast<unsigned char>(r) & 0xff) << 24) 
		+ ((static_cast<unsigned char>(g) & 0xff) << 16)
		+ ((static_cast<unsigned char>(b) & 0xff) << 8)
		+ (static_cast<unsigned char>(a) & 0xff);
}